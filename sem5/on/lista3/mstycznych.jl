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
	if abs(v) < epsilon
		return (x0,v,0,0)
	end
	
	# pętla wykonywana ograniczoną liczbę razy
	for k in 1:maxit
		# sprawdzanie czy pochodna jest dopuszczalna
		if pf(x0) == 0
			return (x0,v,k,2)
		end
		
		# następny element ciągu
		x1 = x0 - v/pf(x0)
		v = f(x1)

		# sprawdzenie czy osiągnięto oczekiwaną dokładność
		if abs(x1-x0) < delta || abs(v) < epsilon
			return (x1,v,k,0)
		end

		x0 = x1
	end

	# nie osiągnięto oczekiwanego przybliżenia w oczekiwanej liczbie iteraci - zwracamy obecne przybliżenie z błędem
	return (x0,f(x0),maxit,1)
end