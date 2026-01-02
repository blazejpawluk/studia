function matvec_block(n::Int, l::Int, diag::Vector{Matrix{Float64}},
					sub::Vector{Matrix{Float64}}, sup::Vector{Matrix{Float64}},
					x::Vector{Float64})
	v = div(n,l)

	xb = [x[(k-1)*l+1 : k*l] for k in 1:v]
	bb = [zeros(Float64, l) for k in 1:v]
	for k in 1:v
		bb[k] .+= diag[k] * xb[k]

		if k >= 2
			bb[k] .+= sub[k] * xb[k-1]
		end

		if k <= v-1
			bb[k] .+= sup[k] * xb[k+1]
		end
	end

	return vcat(bb...)
end