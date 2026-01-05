# Błażej Pawluk, 279738

# funkcja wyliczająca wektor b, dla x = (1,...,1)^T (b=Ax)
function calc_b(n, l, A, B, C)
	b = zeros(Float64, n)
	v = div(n, l)

	for k in 1:v
		for i in 1:l
			for j in 1:l
				b[(k-1)*l + i] += A[k][i,j]
				if k != 1
					b[(k-1)*l + i] += B[k][i,j]
				end
				if k != v
					b[(k-1)*l + i] += C[k][i,j]
				end
			end
		end
	end

	return b
end