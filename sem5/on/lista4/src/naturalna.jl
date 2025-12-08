# Błażej Pawluk, 279738

module Naturalna

export naturalna

function naturalna(x::Vector{Float64}, fx::Vector{Float64})
	m = length(x) # n+1

	a = zeros(Float64, m) # wektor wynikowy

	a[1] = fx[m] # zaczynamy od najwyższego współczynnika Newtona

	for k in m-1:-1:1 # iteracja po węzłach
		xk = x[k] # aktualny węzęł
		ck = fx[k] # aktualny współczynnik Newtona

		for j in m:-1:2 # iteracja od najwyższej potęgi do najmniejszej
			a[j] = a[j-1] - xk*a[j]
		end

		a[1] = ck - xk*a[1] # wyraz wolny aktualizowany oddzielnie
	end

	return a
end

end