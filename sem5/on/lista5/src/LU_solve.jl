# Błażej Pawluk, 279738

include("matrix_helper.jl")

# funkcja obliczająca wynik x równania LUx = b
# macierz blokowa A nxn, rozłożona do postaci LU, bloki o stałym rozmiarze lxl, podana w postaci 
#	A - bloki na przekątnej (gęste) w U, 
#	C - bloki nad przekątną (diagonalna) w U,
#	Y - bloki pod przekątną (macierze zerujące element B z macierzy A) w L
function LU_solve(n, l, A, C, Y, b; pivot=pivot)
	v = div(n, l)

	right = [b[(k-1)*l+1 : k*l] for k in 1:v] # podział wektora na bloki

	# krok 1: Ly = b
	y = Vector{Vector{Float64}}(undef, v)
	y[1] = right[1] # y[1] = b[1]
	for k in 2:v
		y[k] = right[k] - mul_matrix_vector(Y[k-1], y[k-1]) # y[k] = b[k] - Y[k]*y[k-1]
	end

	# krok 2: Ux = y
	x = Vector{Vector{Float64}}(undef, v)
	x[v] = gauss_solve(A[v], y[v]) # A[v]*x[v] = y[v]
	for k in v-1:-1:1
		x[k] = gauss_solve(A[k], y[k] - mul_matrix_vector(C[k], x[k+1]); pivot=pivot) # A[k]*x[k] = y[k] - C[k]*x[k+1]
	end

	# złożenie wyniku do jednego wektora
	result = zeros(Float64, n)
	for k in 1:v
		result[(k-1)*l+1 : k*l] = x[k]
	end

	return result
end