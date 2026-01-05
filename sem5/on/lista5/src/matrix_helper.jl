# Błażej Pawluk, 279738

# funkcja pomocnicza obliczająca wynik x równania Mx = b korzystając z eliminacji Gaussa (z opcjonalnym częściowym wyborem elementu głównego), gdzie
# 	M - macierz gęsta nxn
# 	b - wektor o długości n
function gauss_solve(M, b; pivot=false)
	n = length(b)

	# tworzenie kopii
	M = copy(M)
	v = copy(b)

	# transformacja do posiaci górnotrójkątnej
	for k in 1:n-1
		p = k # element główny

		# opcjonalne wybieranie częściowe elementu głównego
		if pivot
			# wybierz największy element w kolumnie
			maxval = abs(M[k,k])
			for i in k+1:n
				if abs(M[i,k]) > maxval
					maxval = abs(M[i,k])
					p = i
				end
			end
		end
		if p != k
			# zamiana wierszy
			M[k,:], M[p,:] = M[p,:], M[k,:]
			v[k], v[p] = v[p], v[k]
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

# funkcja pomocnicza obliczająca wynik Y równania YA = B (z opcjonalnym częściowym wyborem elementu głównego), gdzie
# 	A - macierz gęsta nxn
# 	B - macierz nxn o niezerowych pierwszym wierszu i ostatniej kolumnie 
function solve_Y(A, B; pivot=false)
	n = size(A,1)
	Y = zeros(Float64, n, n)

	# transpozycja ręczna A
	At = Array{Float64}(undef, n, n)
	for i in 1:n, j in 1:n
		At[i,j] = A[j,i]
	end

	# rozwiązujemy tylko potrzebne wiersze
	for i in 1:n
		bvec = [B[i,j] for j in 1:n] # b^T
		x = gauss_solve(At, bvec; pivot=pivot) # (A^T) x = b^T
		for j in 1:n
			Y[i,j] = x[j]
		end
	end

	return Y
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