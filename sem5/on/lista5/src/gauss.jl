# Błażej Pawluk, 279738

include("matrix_helper.jl")

# funkcja obliczająca wynik x równania Ax = b (z opcjonalnym częściowym wyborem elementu głównego w obliczeniach w blokach)
# macierz blokowa A nxn, bloki o stałym rozmiarze lxl, podana w postaci 
#	diag - bloki na przekątnej (gęste), 
#	sub - bloki pod przekątną (tylko pierwszy wiersz i ostatnia kolumna niezerowe), 
#	sup - bloki nad przekątną (diagonalna)
function gauss(n, l, diag, sub, sup, b; pivot=false)
	v = div(n,l)

	# tworzenie kopii
	A = deepcopy(diag)
	B = deepcopy(sub)
	C = deepcopy(sup)
	right = [copy(b[(k-1)*l+1 : k*l]) for k in 1:v] # podział wektora na bloki

	# krok 1: eliminacja do postaci górnotrójkątnej
	for k in 1:v-1
		Y = solve_Y(A[k], B[k+1]; pivot=pivot) # Y*A[k] = B[k+1]

		A[k+1] -= mul_matrix_diag(Y,C[k]) # A[k+1] <- A[k+1] - Y*C[k]
		right[k+1] -= mul_matrix_vector(Y,right[k]) # b[k+1] <- b[k+1] - Y*b[k]
		B[k+1] .= 0 # B[k+1] <- B[k+1] - Y*A[k] = 0
	end

	# krok 2: podstawianie wsteczne
	x = zeros(Float64, n) # wektor wynikowy
	x[(v-1)*l+1 : v*l] = gauss_solve(A[v], right[v]; pivot=pivot) # ostatni wiersz - A[v]*x[v] = b[v]
	for k in v-1:-1:1
		# pozostałe wiersze - A[k]*x[k] + C[k]*x[k+1] = b[k]
		x[(k-1)*l+1 : k*l] = gauss_solve(A[k], right[k] - mul_matrix_vector(C[k], x[k*l+1 : (k+1)*l]); pivot=pivot)
	end

	return x
end