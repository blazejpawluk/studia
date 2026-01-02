function gaussian_block_solve(n::Int, l::Int, diag_in::Vector{Matrix{Float64}},
							sub_in::Vector{Matrix{Float64}}, sup_in::Vector{Matrix{Float64}},
							b::Vector{Float64}; pivot::Bool=false)
		v = div(n, l)

		diag = [copy(diag_in[k]) for k in 1:v]
		sub  = [copy(sub_in[k])  for k in 1:v]
		sup  = [copy(sup_in[k])  for k in 1:v]

		bblocks = [copy(b[(k-1)*l+1 : k*l]) for k in 1:v]

		LUblocks = Vector{Matrix{Float64}}(undef, v)
		pivots = Vector{Vector{Int}}(undef, v)

		for k in 1:v-1
			LU, piv = lu_factor_small(diag[k]; pivot = pivot)
			LUblocks[k] = LU
			pivots[k] = piv
			X = lu_solve_small(LU, piv, sup[k])
			diag[k+1] .-= sub[k+1] * X
			tvec = lu_solve_small(LU, piv, reshape(bblocks[k], l, 1))
			bblocks[k+1] .-= sub[k+1] * vec(tvec)
		end

		LU, piv = lu_factor_small(diag[v]; pivot = pivot)
		LUblocks[v] = LU
		pivots[v] = piv

		xblocks = [zeros(Float64, l) for _ in 1:v]
		xblocks[v] = lu_solve_small(LUblocks[v], pivots[v], reshape(bblocks[v], l, 1)) |> vec
		for k in v-1:-1:1
			rhs = bblocks[k] - sup[k] * xblocks[k+1]
			xblocks[k] = lu_solve_small(LUblocks[k], pivots[k], reshape(rhs, l, 1)) |> vec
		end

		return vcat(xblocks...)
end