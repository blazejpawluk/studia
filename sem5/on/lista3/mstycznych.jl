# Błażej Pawluk

# funkcja znajdująca miejsce zerowe funkcji z podanymi dokładnościami metodą Newtona (stycznych)
function mstycznych(
	f,					# funkcja anonimowa
	pf,					# pochodna funkcji f, funkcja anonimowa
	x0::Float64,		# przybliżenie początkowe
	delta::Float64,		# dokładność pierwiastka
	epsilon::Float64,	# dokładność wyniku
	maxit::Int			# maksymalna liczba iteracji
)
	v = f(x0) # aktualna wartość funkcji

	# sprawdzenie obecnego wyniku
	if abs(v) <= epsilon
		return (x0,v,0,0)
	end
	
	# główna pętla wykonywana ograniczoną liczbę razy
	for it in 1:maxit
		# sprawdzanie czy pochodna jest dopuszczalna
		if pf(x0) == 0
			return (x0,v,it,2)
		end
		
		# następny element ciągu
		r = x0 - v/pf(x0)
		v = f(r)

		# sprawdzenie czy osiągnięto oczekiwaną dokładność
		if abs(r-x0) <= delta || abs(v) <= epsilon
			return (r,v,it,0)
		end

		x0 = r
	end

	# nie osiągnięto oczekiwanego przybliżenia w oczekiwanej liczbie iteraci - zwracamy obecne przybliżenie z błędem
	return (x0,f(x0),maxit,1)
end