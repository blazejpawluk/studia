# Błażej Pawluk, 279738

module WarNewton

export warNewton

function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
	m = length(x) # n+1

	nt = fx[m] # rozpoczynamy od najwyzszego wspolczynnika (ilorazu rzedu n)

	# uogolniony horner
	for k in m-1:-1:1
		nt = fx[k] + (t - x[k]) * nt
	end

	return nt
end

end