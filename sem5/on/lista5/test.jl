# Błażej Pawluk, 279738
# plik testujący funkcje

include("src/blocksys.jl")
using .blocksys
using LinearAlgebra

# macierz wejściowa
print("Macierz A: ")
a_file = readline()
println("Wczytywanie macierzy z fliku ", a_file, "...\n")
n, l, diag, sub, sup = read_matrix(a_file)

# wektor wejściowy (nie znaleziony - wyliczany z (1,...,1)^T)
print("Wektor b: ")
b_file = readline()
b = undef
b_from_file = false
try
	println("Wczytywanie wektora z pliku ", b_file, "...\n")
	global b = read_vector(b_file)
	global b_from_file = true
catch
	println("Nie udało się wczytać wektora z pliku. Generowanie b z równania b = Ax, gdzie x=(1,..,1)^T")
	global b = calc_b(n, l, diag, sub, sup)
end

# plik wyjściowy
print("Plik wyjściowy: ")
out_file = readline()

# metoda (G - Gauss, LU, B - both)
println("Metoda obliczenia równania Ax = b:")
println("\tG - metoda eliminacji Gaussa")
println("\tLU - metoda przez rozkład A do postaci LU i obliczenie wyniku z LUx = b")
method = readline()

# wybór elementu głównego (T/N)
print("Funkcja z częściowym wyborem elementu głównego? (T/N): ")
p = readline()
pivot = (p == "T" ? true : false)

x = undef
if method == "G"
	x = gauss(n, l, diag, sub, sup, b; pivot=pivot)
elseif method == "LU"
	A, C, Y = LU_decomposition(n, l, diag, sub, sup; pivot=false)
	x = LU_solve(n, l, A, C, Y, b)
else
	println("Nieznana metoda.")
	exit()
end

if b_from_file
	write_vector(out_file, x)
else
	write_vector(out_file, x; norm=norm(x - ones(Float64, n)))
end