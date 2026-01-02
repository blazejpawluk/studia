using LinearAlgebra
using Plots

include("src/blocksys.jl")
using .blocksys

# Pliki i foldery
input_dir  = "input"
output_dir = "output"

norms_file = joinpath(output_dir, "norms.txt")
times_file = joinpath(output_dir, "times.txt")

isdir(output_dir) || mkdir(output_dir)

# Nagłówki tabel
open(norms_file, "w") do io
	println(io, "\\begin{tabular}{c|c|c|c|c}")
	println(io, "n & wynik 1a & wynik 1b & wynik 3a & wynik 3b \\\\")
	println(io, "\\hline")
end

open(times_file, "w") do io
	println(io, "\\begin{tabular}{c|c|c|c|c|c|c}")
	println(io, "n & czas 1a & czas 1b & czas 3a & czas 3b \\\\")
	println(io, "\\hline")
end

# Pobieranie danych i sortowanie po rozmiarach
folders = Tuple{Int,String}[]

for entry in readdir(input_dir; join = true)
	isdir(entry) || continue
	try
		n = parse(Int, basename(entry))
		push!(folders, (n, entry))
	catch
	end
end
sort!(folders, by = x -> x[1])

# Tablice na dane do wykresu
ns = Int[]
t1a_list = Float64[]
t1b_list = Float64[]
t3a_list = Float64[]
t3b_list = Float64[]

# przetwarzanie danych
for (n_from_dir, entry) in folders
	println("Przetwarzanie danych dla n = ", n_from_dir)

	# Pliki wejściowe
	A_file = joinpath(entry, "A.txt")
	b_file = joinpath(entry, "b.txt")

	# Katalog wyjściowy
	out_n_dir = joinpath(output_dir, string(n_from_dir))
	isdir(out_n_dir) || mkdir(out_n_dir)

	x1a_file  = joinpath(out_n_dir, "x_1a_gauss.txt")
	x1b_file  = joinpath(out_n_dir, "x_1b_gauss.txt")
	x3a_file = joinpath(out_n_dir, "x_3a_lu_nopiv.txt")
	x3b_file = joinpath(out_n_dir, "x_3b_lu_piv.txt")

	# Wczytanie danych
	(n, l, diag, sub, sup) = read_block_matrix(A_file)
	b = read_vector(b_file)

	# ZADANIE 1a – Gauss bez pivotingu
	t1a = @elapsed begin
		x1a = gaussian_block_solve(n, l, diag, sub, sup, b; pivot = false)
	end
	write_vector(x1a_file, x1a)

	norm1a = norm(matvec_block(n, l, diag, sub, sup, x1a) - b)

	# ZADANIE 1b – Gauss z pivotingiem
	t1b = @elapsed begin
		x1b = gaussian_block_solve(n, l, diag, sub, sup, b; pivot = true)
	end
	write_vector(x1b_file, x1b)

	norm1b = norm(matvec_block(n, l, diag, sub, sup, x1b) - b)

	# ZADANIE 3a – solve LU bez pivotingu
	t3a = @elapsed begin
		(LUa, piva, Lsuba, Usupa) = block_lu_factor(n, l, diag, sub, sup; pivot = false)
		x3a = block_lu_solve(n, l, LUa, piva, Lsuba, Usupa, b)
	end
	write_vector(x3a_file, x3a)
	
	norm3a = norm(matvec_block(n, l, diag, sub, sup, x3a) - b)
	
	# ZADANIE 3b – solve LU z pivotingiem
	t3b = @elapsed begin
		(LUb, pivb, Lsubb, Usupb) = block_lu_factor(n, l, diag, sub, sup; pivot = true)
		x3b = block_lu_solve(n, l, LUb, pivb, Lsubb, Usupb, b)
	end
	write_vector(x3b_file, x3b)

	norm3b = norm(matvec_block(n, l, diag, sub, sup, x3b) - b)

	# Zapis norm
	open(norms_file, "a") do io
		println(io, string(n, " & ", norm1a, " & ", norm1b, " & ", norm3a, " & ", norm3b, " \\\\"))
	end

	# Zapis czasów
	open(times_file, "a") do io
		println(io, string(n, " & ", t1a, " & ", t1b, " & ", t3a, " & ", t3b, " \\\\"))
	end

	# Zapis danych do wykresu
	push!(ns, n_from_dir)
	push!(t1a_list, t1a)
	push!(t1b_list, t1b)
	push!(t3a_list, t3a)
	push!(t3b_list, t3b)
end

# Zamykanie tabel LaTeX
open(norms_file, "a") do io
	println(io, "\\end{tabular}")
end

open(times_file, "a") do io
	println(io, "\\end{tabular}")
end

# Rysowanie wykresu
println("Tworzenie wykresu")
plot(ns, t1a_list, label="Gauss bez pivotingu", marker=:o, lw=2, grid=true)
plot!(ns, t1b_list, label="Gauss z pivotingiem", marker=:o, lw=2)
plot!(ns, t3a_list, label="LU bez pivotingu", marker=:o, lw=2)
plot!(ns, t3b_list, label="LU z pivotingiem", marker=:o, lw=2)

xlabel!("Rozmiar macierzy n")
ylabel!("Czas [s]")
title!("Czasy wykonania metod")
savefig(joinpath(output_dir, "times_plot.png"))

println("\nZakończono przetwarzanie.")