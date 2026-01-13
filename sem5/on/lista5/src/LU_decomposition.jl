# Błażej Pawluk, 279738

# funkcja obliczająca rozkład macierzy A do iloczynu LU (z opcjonalnym częściowym wyborem elementu głównego w obliczeniach w blokach)
# macierz blokowa A nxn, bloki o stałym rozmiarze lxl, podana w postaci 
#	diag - bloki na przekątnej (gęste), 
#	sub - bloki pod przekątną (tylko pierwszy wiersz i ostatnia kolumna niezerowe), 
#	sup - bloki nad przekątną (diagonalna)
function LU_decomposition(n, l, diag, sub, sup; pivot=false)
	v = div(n,l)

	# tworzenie struktury LU
	A = diag
	C = sup
	# A = copy(diag)
	# C = copy(sup)
	Y = Vector{Matrix{Float64}}()

	for k in 1:v-1
		Yk = solve_Y(A[k], sub[k+1]; pivot=pivot) # Y*A[k] = B[k+1]
		push!(Y, Yk)

		A[k+1] -= mul_matrix_diag(Yk,C[k]) # A[k+1] <- A[k+1] - Y*C[k]
	end

	return (A, C, Y)
end