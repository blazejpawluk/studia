# Błażej Pawluk, 279738

module IlorazyRoznicowe

export ilorazyRoznicowe

function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})
	m = length(x) # n+1

	fx = copy(f) # pracujemy na kopii, która jest zwracana
	for j in 2:m # j - poziom ilorazu roznicowego
		for i in m:-1:j # i - indeks poczatkowy dla danego ilorazu
			fx[i] = (fx[i] - fx[i-1]) / (x[i] - x[i - j + 1])
		end
	end

	return fx
end

end