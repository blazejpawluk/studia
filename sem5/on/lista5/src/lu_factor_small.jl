function lu_factor_small(A::Matrix{Float64}; pivot::Bool=false)
	n = size(A,1)
	@assert size(A,1) == size(A,2)
	LU = copy(A)
	piv = collect(1:n)
	for k in 1:n-1
		if pivot
			maxrow = k
			maxval = abs(LU[k,k])
			for i in k+1:n
				v = abs(LU[i,k])
				if v > maxval
					maxval = v
					maxrow = i
				end
			end
			if maxval == 0.0
				error("Singular matrix detected during LU factorization (zero pivot).")
			end
			if maxrow != k
				LU[k, :], LU[maxrow, :] = LU[maxrow, :], LU[k, :]
				piv[k], piv[maxrow] = piv[maxrow], piv[k]
			end
		else
			if LU[k,k] == 0.0
				error("Zero pivot encountered and pivoting disabled.")
			end
		end
		for i in k+1:n
			LU[i,k] = LU[i,k] / LU[k,k]
			for j in k+1:n
				LU[i,j] -= LU[i,k] * LU[k,j]
			end
		end
	end
	if LU[n,n] == 0.0
		error("Zero pivot in last diagonal; singular.")
	end
	return LU, piv
end