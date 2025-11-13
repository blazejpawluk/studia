# Błażej Pawluk

# funkcja znajdująca miejsce zerowe funkcji w podanym przedziale i z podanymi dokładnościami metodą bisekcji
function mbisekcji(
	f,					# funkcja anonimowa
	a::Float64,			# lewa granica przedziału
	b::Float64,			# prawa granica przedziału
	delta::Float64,		# dokładność pierwiastka
	epsilon::Float64	# dokładność wyniku
)
	valL = f(a)	# wartość na lewej granicy
	valR = f(b)	# wartość na prawej granicy
	e = b-a		# wielkość przedziału
	r = a+e		# środek przedziału
	v = f(r)	# wartość na środku przedziału
	it = 0		# liczba iteracji

	# sprawdzenie wartości na granicach
	if valL == 0
		return (a,valL,0,0)
	elseif valR == 0
		return (b,valR,0,0)
	end

	# wykrycie tego samego znaku na końcu przedziałów
	if valL*valR > 0
		return (0,0,0,1)
	end

	# główna pętla
	while abs(e) > delta && abs(v) > epsilon
		it += 1 # zliczanie iteracji

		# zmiana współczynników
		e /= 2.0
		r = a+e
		v = f(r)

		# sprawdzenie znaków, aby zdecydować, który przedział wybrać
		if v == 0
			return (r,v,it,0)
		elseif valL*v > 0
			a = r
			valL = v
		else
			b = r
			valR = v
		end
	end
	return (r,v,it,0)
end