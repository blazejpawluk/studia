#!/usr/bin/env bash

API_URL="http://localhost:3000/api"

CHECK() {
	local code=$1
	local label=$2
	if [ "$code" -ge 200 ] && [ "$code" -lt 300 ]; then
		echo "SUKCES: $label -> HTTP $code"
	else
		echo "PORAZKA: $label -> HTTP $code"
	fi
}

# plik tymczasowy na odpowiedzi
# TMP_RESP=$(mktemp)
TMP_RESP="./tmp_response.json"

echo "W bazie znajduje sie tylko konto admina"

echo "1) Rejestracja usera - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/register" \
	-H "Content-Type: application/json" \
	-d '{"nickname":"user1", "email":"user@user.pl", "password":"password"}')
CHECK "$HTTP" "POST /auth/register"
echo

USER_TOKEN=$(grep -o '"token"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
			| sed 's/.*"token"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')
echo "Zapisano token usera."

USER_ID=$(grep -o '"id"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
		| sed 's/.*"id"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')
echo "Zapisano ID usera."
echo

echo "2) Rejestracja na uzyty adres email - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/register" \
	-H "Content-Type: application/json" \
	-d '{"nickname":"user2", "email":"user@user.pl", "password":"password"}')
CHECK "$HTTP" "POST /auth/register"
echo

echo "3) Logowanie usera - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/login" \
	-H "Content-Type: application/json" \
	-d '{"email":"user@user.pl", "password":"password"}')
CHECK "$HTTP" "POST /auth/login"
echo

USER_TOKEN=$(grep -o '"token"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
			| sed 's/.*"token"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')
echo "Token zwyklego uzytkownika zapisany."
echo

echo "4) Logowanie ze zlym haslem - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/login" \
	-H "Content-Type: application/json" \
	-d '{"email":"user@user.pl", "password":"wrongpassword"}')
CHECK "$HTTP" "POST /auth/login"
echo

echo "5) Dane konta admina"
read -p "email: " ADMIN_EMAIL
read -s -p "haslo: " ADMIN_PASS
echo

echo "6) Logowanie admina - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/login" \
	-H "Content-Type: application/json" \
	-d "{\"email\":\"$ADMIN_EMAIL\", \"password\":\"$ADMIN_PASS\"}")
CHECK "$HTTP" "POST /auth/login"
echo

ADMIN_TOKEN=$(grep -o '"token"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
			| sed 's/.*"token"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')
echo "Token admina zapisany."
echo

echo "7) Wyswietlenie pustej listy filmow bedac niezalogowanym - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
		"$API_URL/films?page=1&limit=5")
CHECK "$HTTP" "GET /films?page=1&limit=5"
echo

echo "8) Dodanie filmu jako user - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/films" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $USER_TOKEN" \
	-d '{"name":"film", "genre":"other", "releaseYear":2000}')
CHECK "$HTTP" "POST /films"
echo

echo "9) Dodanie filmu jako admin - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/films" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $ADMIN_TOKEN" \
	-d '{"name":"film", "genre":"other", "releaseYear":2000}')
CHECK "$HTTP" "POST /films"
echo

FILM_ID=$(grep -o '"_id"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
		| sed 's/.*"_id"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')
echo "Zapisano ID filmu."
echo

echo "10) Pobranie listy filmow bez logowania - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
		"$API_URL/films?page=1&limit=5")
CHECK "$HTTP" "GET /films?page=1&limit=5"
echo

COUNT=$(grep -o '"data"[[:space:]]*:[[:space:]]*\[[^]]*\]' "$TMP_RESP" \
		| sed 's/.*\[\(.*\)\].*/\1/' \
		| awk -F '},' '{print NF}')
echo "Liczba filmow (oczekiwane 1): $COUNT" 
echo

echo "11) Wyswietlenie dodanego filmu - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
  	"$API_URL/films/$FILM_ID")
CHECK $HTTP "GET /films/$FILM_ID"
echo

echo "12) Dodanie recenzji bez logowania - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/reviews/film/$FILM_ID" \
	-H "Content-Type: application/json" \
	-d '{"rating":1, "description":"aaa"}')
CHECK $HTTP "POST /reviews/film/$FILM_ID"
echo

echo "13) Dodanie recenzji ze zla ocena - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/reviews/film/$FILM_ID" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $USER_TOKEN" \
	-d '{"rating":11, "description":"aaa"}')
CHECK $HTTP "POST /reviews/film/$FILM_ID"
echo

echo "14) Dodanie poprawnej recenzji jako user - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/reviews/film/$FILM_ID" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $USER_TOKEN" \
	-d '{"rating":2, "description":"aaa"}')
CHECK $HTTP "POST /reviews/film/$FILM_ID"
echo

REV_ID=$(
	node -e "
		const fs = require('fs');
		const obj = JSON.parse(fs.readFileSync('$TMP_RESP', 'utf8'));
		console.log(obj._id);
	"
)
echo "Zapisano ID recenzji."
echo

echo "15) Pobranie recenzji filmu - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	"$API_URL/reviews/film/$FILM_ID")
CHECK $HTTP "GET /reviews/film/$FILM_ID"
echo

REVS=$(
  node -e "
    const fs = require('fs');
    const obj = JSON.parse(fs.readFileSync('${TMP_RESP}', 'utf8'));
    console.log((obj.data || []).length);
  "
)
echo "Liczba recenzji (oczekiwana 1): $REVS"
echo

echo "16) Usuniecie recenzji innym userem (rejestracja nowego i proba usuniecia) - oczekiwana porazka"
HTTP=$(curl -s -X POST "$API_URL/auth/register" -H "Content-Type: application/json" \
	-d '{"nickname":"user2", "email":"user2@user2.pl", "password":"password"}')
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/login" \
	-H "Content-Type: application/json" \
	-d '{"email":"user2@user2.pl", "password":"password"}')

USER2_TOKEN=$(grep -o '"token"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
			| sed 's/.*"token"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')
USER2_ID=$(grep -o '"id"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
			| sed 's/.*"id"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')

HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/reviews/$REV_ID" \
	-H "Authorization: Bearer $USER2_TOKEN")
CHECK $HTTP "DELETE /reviews/$REV_ID"
echo

echo "17) Usuniecie recenzji przez autora - oczekiwany suckes"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/reviews/$REV_ID" \
	-H "Authorization: Bearer $USER_TOKEN")
CHECK $HTTP "DELETE /reviews/$REV_ID"
echo

echo "18) Edycja filmu przez autora - oczekiwana porażka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X PATCH "$API_URL/films/$FILM_ID" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $USER_TOKEN" \
	-d '{"name":"film zmieniony zle"}')
CHECK $HTTP "PATCH /films/$FILM_ID"
echo

echo "19) Edycja filmu przez admina - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X PATCH "$API_URL/films/$FILM_ID" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $ADMIN_TOKEN" \
	-d '{"name":"film zmieniony dobrze"}')
CHECK $HTTP "PATCH /films/$FILM_ID"
echo

echo "20) Usuniecie filmu przez usera - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/films/$FILM_ID" \
	-H "Authorization: Bearer $USER_TOKEN")
CHECK $HTTP "DELETE /films/$FILM_ID"
echo

echo "21) Usuniecie filmu przez admina - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/films/$FILM_ID" \
	-H "Authorization: Bearer $ADMIN_TOKEN")
CHECK $HTTP "DELETE /films/$FILM_ID"
echo

echo "22) Wyswietlenie usunietego filmu - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
  	"$API_URL/films/$FILM_ID")
CHECK $HTTP "GET /films/$FILM_ID"
echo

echo "23) Wyswietlenie userow jako user - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X GET "$API_URL/users" \
	-H "Authorization: Bearer $USER_TOKEN")
CHECK $HTTP "GET /users"
echo

echo "24) Wyswietlenie userow jako admin - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X GET "$API_URL/users" \
	-H "Authorization: Bearer $ADMIN_TOKEN")
CHECK $HTTP "GET /users"
echo

USER_COUNT=$(
	node -e "
		const fs = require('fs');
		const obj = JSON.parse(fs.readFileSync('$TMP_RESP', 'utf8'));
		console.log((obj.data || []).length);
	"
)
echo "Liczba uzytkownikow (oczekiwane 3): $USER_COUNT"
echo

echo "25) Wyswietlenie usera przez innego usera - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X GET "$API_URL/users/$USER2_ID" \
	-H "Authorization: Bearer $USER_TOKEN")
CHECK $HTTP "GET /users/$USER2_ID"
echo

echo "26) Wyswietlenie usera przez admina - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X GET "$API_URL/users/$USER_ID" \
	-H "Authorization: Bearer $ADMIN_TOKEN")
CHECK $HTTP "GET /users/$USER_ID"
echo

echo "27) Wyswietlenie siebie przez usera - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X GET "$API_URL/users/$USER_ID" \
	-H "Authorization: Bearer $USER_TOKEN")
CHECK $HTTP "GET /users/$USER_ID"
echo

echo "28) Zmiana danych usera przez innego usera - oczekiwana porazka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X PUT "$API_URL/users/$USER_ID" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $USER2_TOKEN" \
	-d '{"nickname":"unauthorized_update"}')
CHECK $HTTP "PUT /users/$USER_ID"
echo

echo "29) Zmiana swoich danych - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X PUT "$API_URL/users/$USER_ID" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $USER_TOKEN" \
	-d '{"nickname":"user1-zmienionydobrze"}')
CHECK $HTTP "PUT /users/$USER_ID"
echo

echo "30) Usunięcie usera innym userem - oczekiwana porażka"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/users/$USER_ID" \
	-H "Authorization: Bearer $USER2_TOKEN")
CHECK $HTTP "DELETE /users/$USER_ID"
echo

echo "31) Usunięcie własnego konta userem - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/users/$USER2_ID" \
	-H "Authorization: Bearer $USER2_TOKEN")
CHECK $HTTP "DELETE /users/$USER2_ID"
echo

echo "32) Usunięcie konta usera adminem - oczekiwany sukces"
HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X DELETE "$API_URL/users/$USER_ID" \
	-H "Authorization: Bearer $ADMIN_TOKEN")
CHECK $HTTP "DELETE /users/$USER_ID"
echo

rm "$TMP_RESP"

echo "Wszystkie testy wykonane."