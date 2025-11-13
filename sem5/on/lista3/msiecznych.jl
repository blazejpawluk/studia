# Błażej Pawluk

# funkcja znajdująca miejsce zerowe funkcji z podanymi dokładnościami metodą siecznych
function msiecznych(
	f,					# funkcja anonimowa
	x0::Float64,		# przybliżenie początkowe 1
	x1::Float64,		# przybliżenie początkowe 2
	delta::Float64,		# dokładność pierwiastka
	epsilon::Float64,	# dokładność wyniku
	maxit::Int			# maksymalna liczba iteracji
)
	# wartości funkcji w punktach przybliżenia
	f0 = f(x0)
	f1 = f(x1)

	# główna pętla wykonywana ograniczoną liczbę razy
	for it in 1:maxit
		# zmienna x0 musi być bliżej 0
		if abs(f0) > abs(f1)
			temp = x0
			x0 = x1
			x1 = temp

			temp = f0
			f0 = f1
			f1 = temp
		end

		# wyliczanie kolejnego elementu ciągu
		s = (x1-x0)/(f1-f0)
		x1 = x0
		f1 = f0
		x0 -= f0*s
		f0 = f(x0)

		# sprawdzenie warunku końcowego
		if abs(x1-x0) <= delta || abs(f0) <= epsilon
			return (x0,f0,it,0)
		end
	end

	# nie osiągnięto oczekiwanego przybliżenia w oczekiwanej liczbie iteraci - zwracamy obecne przybliżenie z błędem
	return (x0,f0,maxit,1)
end