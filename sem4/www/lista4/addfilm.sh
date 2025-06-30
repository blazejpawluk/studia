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

TMP_RESP="./tmp_response.json"

read -p "email: " ADMIN_EMAIL
read -s -p "haslo: " ADMIN_PASS

HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/auth/login" \
	-H "Content-Type: application/json" \
	-d "{\"email\":\"$ADMIN_EMAIL\", \"password\":\"$ADMIN_PASS\"}")
CHECK "$HTTP" "POST /auth/login"

ADMIN_TOKEN=$(grep -o '"token"[[:space:]]*:[[:space:]]*"[^"]*"' "$TMP_RESP" \
			| sed 's/.*"token"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/')

HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/films" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $ADMIN_TOKEN" \
	-d '{"name":"film1", "genre":"other", "releaseYear":1999}')
CHECK "$HTTP" "POST /films"

HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/films" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $ADMIN_TOKEN" \
	-d '{"name":"film2", "genre":"other", "releaseYear":2000}')
CHECK "$HTTP" "POST /films"

HTTP=$(curl -s -w "%{http_code}" -o "$TMP_RESP" \
	-X POST "$API_URL/films" \
	-H "Content-Type: application/json" \
	-H "Authorization: Bearer $ADMIN_TOKEN" \
	-d '{"name":"film3", "genre":"other", "releaseYear":2001}')
CHECK "$HTTP" "POST /films"

rm "$TMP_RESP"