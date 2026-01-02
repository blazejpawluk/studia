function block_lu_factor(n::Int, l::Int, diag_in::Vector{Matrix{Float64}},
						sub_in::Vector{Matrix{Float64}}, sup_in::Vector{Matrix{Float64}};
						pivot::Bool=false)
	v = div(n,l)
	diag = [copy(diag_in[k]) for k in 1:v]
	sub = [copy(sub_in[k]) for k in 1:v]
	sup = [copy(sup_in[k]) for k in 1:v]
	LUblocks = Vector{Matrix{Float64}}(undef, v)
	pivots = Vector{Vector{Int}}(undef, v)
	Lsub = [zeros(Float64, l, l) for k in 1:v]

	for k in 1:v
		LU, piv = lu_factor_small(diag[k]; pivot=pivot)
		LUblocks[k] = LU
		pivots[k] = piv
		if k < v
			T = lu_solve_small(LU, piv, sup[k])  # l x l
			InvA_times_I = lu_solve_small(LU, piv, Matrix{Float64}(I,l,l))
			Lsub[k+1] .= sub[k+1] * InvA_times_I
			diag[k+1] .-= sub[k+1] * T
		end
	end
	return (LUblocks, pivots, Lsub, sup)
end