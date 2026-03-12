# Błażej Pawluk, 279738

# funkcja pomocnicza obliczająca wynik x równania Mx = b korzystając z eliminacji Gaussa (z opcjonalnym częściowym wyborem elementu głównego), gdzie
# 	M - macierz gęsta nxn
# 	b - wektor o długości n
# funkcja pomocnicza obliczająca wynik x równania Mx = b korzystając z eliminacji Gaussa
# z opcjonalnym częściowym (skalowanym) wyborem elementu głównego
function gauss_solve(M, b; pivot=false)
	n = length(b)

	# tworzenie kopii
	v = b

	# skalowanie wierszy (do skalowanego pivotingu)
	scales = ones(Float64, n)
	if pivot
		for i in 1:n
			scales[i] = maximum(abs.(M[i,:]))
		end
	end

	# transformacja do postaci górnotrójkątnej
	for k in 1:n-1
		p = k # element główny

		# opcjonalny skalowany wybór elementu głównego
		if pivot
			maxval = abs(M[k,k]) / scales[k]
			for i in k+1:n
				val = abs(M[i,k]) / scales[i]
				if val > maxval
					maxval = val
					p = i
				end
			end
		end

		if p != k
			# zamiana wierszy
			M[k,:], M[p,:] = M[p,:], M[k,:]
			v[k], v[p] = v[p], v[k]
			scales[k], scales[p] = scales[p], scales[k]
		end

		if M[k,k] == 0.0
			error("Invalid matrix found")
		end

		# eliminacja
		for i in k+1:n 
			f = M[i,k] / M[k,k] 
			for j in k:n 
				M[i,j] -= f * M[k,j] 
			end 
			v[i] -= f * v[k] 
		end
	end

	# podstawianie wsteczne
	x = zeros(Float64, n)
	for i in n:-1:1
		s = v[i]
		for j in i+1:n
			s -= M[i,j] * x[j]
		end
		x[i] = s / M[i,i]
	end

	return x
end

function small_lu(A; pivoting=false)
	n = size(A, 1)
	U = A
	L = Matrix{Float64}(I, n, n)
	P = collect(1:n)

	for k in 1:n-1
		if pivoting
			pivot = argmax(abs.(U[k:end, k])) + k - 1
			if pivot != k
				U[[k, pivot], :] = U[[pivot, k], :]
				L[[k, pivot], 1:k-1] = L[[pivot, k], 1:k-1]
				P[[k, pivot]] = P[[pivot, k]]
			end
		end

		for i in k+1:n
			L[i, k] = U[i, k] / U[k, k]
			U[i, k:end] .-= L[i, k] * U[k, k:end]
		end
	end

	return L, U, P
end

function small_lu_solve(A, b; pivot=false)
	L, U, P = small_lu(A; pivoting=pivot)
	println(L) 
	println(U) 
	b_perm = b[P]

	n = length(b)
	y = zeros(n)
	x = zeros(n)

	# podstawianie w przód: Ly = Pb
	for i in 1:n
		y[i] = b_perm[i] - sum(L[i, 1:i-1] .* y[1:i-1])
	end

	# podstawianie wstecz: Ux = y
	for i in n:-1:1
		x[i] = (y[i] - sum(U[i, i+1:end] .* x[i+1:end])) / U[i, i]
	end

	return x
end

# oblicza macierz odwrotną metodą Gaussa-Jordana
function inverse_gauss(A; pivot=false)
	n = size(A,1)

	# macierz rozszerzona [A | I]
	M = zeros(Float64, n, 2n)
	M[:,1:n] .= A
	for i in 1:n
		M[i,n+i] = 1.0
	end

	# eliminacja Gaussa-Jordana
	for k in 1:n
		p = k

		if pivot
			maxval = abs(M[k,k])
			for i in k+1:n
				if abs(M[i,k]) > maxval
					maxval = abs(M[i,k])
					p = i
				end
			end
		end

		if p != k
			M[k,:], M[p,:] = M[p,:], M[k,:]
		end

		if M[k,k] == 0.0
			error("Matrix is singular")
		end

		# normalizacja wiersza
		M[k,:] ./= M[k,k]

		# eliminacja w górę i w dół
		for i in 1:n
			if i != k
				f = M[i,k]
				M[i,:] .-= f .* M[k,:]
			end
		end
	end

	return M[:,n+1:2n]
end

# funkcja pomocnicza obliczająca wynik Y równania YA = B (z opcjonalnym częściowym wyborem elementu głównego), gdzie
# 	A - macierz gęsta nxn
# 	B - macierz nxn o niezerowych pierwszym wierszu i ostatniej kolumnie
function solve_Y(A, B; pivot=false)
	Ainv = inverse_gauss(A; pivot=pivot)
	return B * Ainv
end

# funkcja mnożąca przez siebie 2 macierze kwadratowe nxn, gdzie macierz B jest macierzą diagonalną
function mul_matrix_diag(A, B)
	n = size(A, 1)
	C = zeros(Float64, n, n)

	for i in 1:n
		for j in 1:n
			C[i,j] = A[i,j] * B[j,j]
		end
	end

	return C
end

# funkcja mnożąca macierz kwadratową nxn przez wektor o długości n
function mul_matrix_vector(A, b)
	n = size(A,1)
	c = zeros(Float64, n)

	for i in 1:n
		s = 0.0
		for j in 1:n
			s += A[i,j] * b[j]
		end
		c[i] = s
	end

	return c
end