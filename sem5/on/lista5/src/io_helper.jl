# Błażej Pawluk, 279738

# funkcja czytająca macierz w odpowiednim formacie z pliku
# zwraca wartości n oraz l
# zwraca tablice w wartościami nad przekątną (sup), na przekątnej (diag) i pod przekątną (sub)
function read_matrix(filename)
	open(filename, "r") do io

		# wczytywanie danych z pliku
		lines = readlines(io)

		# wyrzucenie pustych linii
		lines = filter(x -> strip(x) != "", lines)

		# sprawdzenie czy w pliku są jakiekolwiek dane
		if length(lines) == 0
			error("Empty file")
		end

		# pierwsza linijka
		firstline = split(strip(lines[1]))
		n = parse(Int, firstline[1])
		l = parse(Int, firstline[2])
		@assert n % l == 0 "n must be divisible by l"
		v = Int(div(n, l))

		# tablice do optymalnego przechowywania macierzy
		diag = [zeros(Float64, l, l) for _ in 1:v] # wartości na przekątnej
		sub = [zeros(Float64, l, l) for _ in 1:v] # wartości pod przekątną
		sup = [zeros(Float64, l, l) for _ in 1:v] # wartości nad przekątną

		# wczytywanie danych
		for line in lines[2:end]
			parts = split(strip(line))

			# sprawdzenie czy linia ma odpowiednią liczbę danych
			if length(parts) < 3
				error("Invalid line found")
			end

			# wczytanie danych z linii
			i = parse(Int, parts[1])
			j = parse(Int, parts[2])
			val = parse(Float64, parts[3])

			# indeksy bloku
			bi = Int(div((i-1), l)) + 1
			bj = Int(div((j-1), l)) + 1

			# indeksy w bloku
			li = (i-1) % l + 1
			lj = (j-1) % l + 1

			# sprawdzenie, do której tablicy powinna zostać przyporządkowana wartość z tej linijki
			if bi == bj
				diag[bi][li, lj] = val
			elseif bi == bj + 1
				sub[bi][li, lj] = val
			elseif bi + 1 == bj
				sup[bi][li, lj] = val
			else
				error("Element detected at invalid position: ($i,$j)")
			end
		end
		
		return (n, l, diag, sub, sup)
	end
end

# funkcja wczytująca wektor w odpowiednim formacie z pliku
# zwraca wektor w tablicy
function read_vector(filename)
	v = Float64[] # wynik
	open(filename, "r") do io

		# wczytywanie danych z pliku
		lines = readlines(io)

		# wyrzucenie pustych linii
		lines = filter(x -> strip(x) != "", lines)

		# sprawdzenie czy w pliku są jakiekolwiek dane
		if length(lines) < 1
			error("Empty file")
		end

		# wczytanie długości pliku
		n = parse(Int, split(strip(lines[1]))[1])

		# sprawdzenie czy ilość danych zgadza się z podaną długością
		if length(lines) < n+1
			error("b file has fewer lines than expected")
		end

		# wczytywanie danych
		for i in 1:n
			push!(v, parse(Float64, strip(lines[i+1])))
		end
	end

	return v
end

# funkcja wypisująca do pliku błąd i wektor wynikowy
function write_vector(filename, x; norm=-1)
    open(filename, "w") do io
		# wypisanie błędu (jeśli podany)
		if norm >= 0 
			println(io, norm)
		end

		# wypisywanie wartości wektora
        for i in eachindex(x)
            println(io, x[i])
        end
    end
end