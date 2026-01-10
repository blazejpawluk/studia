# Błażej Pawluk, 279738
# plik do generowania danych eksperymentów z plików ze strony

include("src/blocksys.jl")
using .blocksys
using LinearAlgebra
using Plots
using Printf

# folder z danymi wejściowymi
input_dir  = "input"

# folder na wyniki
output_dir = "output/files"
isdir(output_dir) || mkdir(output_dir)

# tworzenie plików wynikowych z błędami i czasami
norms_file = joinpath(output_dir, "norms.txt")
times_file = joinpath(output_dir, "times.txt")

# tworzenie nagłówków do plików z błędami i czasami
open(norms_file, "w") do io
	println(io, "\\begin{tabular}{c|c|c|c|c}")
	println(io, "n & wynik 1a & wynik 1b & wynik 2a + 3 & wynik 2b + 3 \\\\")
	println(io, "\\hline")
end

open(times_file, "w") do io
	println(io, "\\begin{tabular}{c|c|c|c|c}")
	println(io, "n & czas 1a & czas 1b & czas 2a3 & czas 2b3 \\\\")
	println(io, "\\hline")
end

# tablice na dane do wykresu
ns = Int[]
t1a_list = Float64[]
t1b_list = Float64[]
t2a3_list = Float64[]
t2b3_list = Float64[]

# pobieranie wszystkich folderów z danymi i sortowanie ich po rozmiarze
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

# przetwarzanie danych
for (n_from_dir, entry) in folders
	println("Przetwarzanie danych dla n = ", n_from_dir)

	# pliki wejściowe
	A_file = joinpath(entry, "A.txt")
	B_file = joinpath(entry, "b.txt")

	# katalog wyjściowy
	out_n_dir = joinpath(output_dir, string(n_from_dir))
	isdir(out_n_dir) || mkdir(out_n_dir)

	# pliki wyjsciowe
	file_1a = joinpath(out_n_dir, "1a.txt")
	file_1b = joinpath(out_n_dir, "1b.txt")
	file_2a3 = joinpath(out_n_dir, "2a3.txt")
	file_2b3 = joinpath(out_n_dir, "2b3.txt")

	# dane do obliczeń
	n, l, diag, sub, sup = read_matrix(A_file)
	b = calc_b(n, l, diag, sub, sup)
	x_true = ones(Float64, n)

	# ZADANIE 1 - Gauss
	# bez wyboru elementu głównego
	time_1a = @elapsed begin
		x_1a = gauss(n, l, diag, sub, sup, b; pivot=false)
	end
	norm_1a = norm(x_true - x_1a) / norm(x_true)
	write_vector(file_1a, x_1a; norm=norm_1a)

	# z wyborem elementu głównego
	time_1b = @elapsed begin
		x_1b = gauss(n, l, diag, sub, sup, b; pivot=true)
	end
	norm_1b = norm(x_true - x_1b) / norm(x_true)
	write_vector(file_1b, x_1b; norm=norm_1b)

	# ZADANIE 2+3 - LU
	# bez wyboru elementu głównego
	time_2a3 = @elapsed begin
		A, C, Y = LU_decomposition(n, l, diag, sub, sup; pivot=false)
		x_2a3 = LU_solve(n, l, copy(A), copy(C), copy(Y), b; pivot=false)
	end
	norm_2a3 = norm(x_true - x_2a3) / norm(x_true)
	write_vector(file_2a3, x_2a3; norm=norm_2a3)

	# z wyborem elementu głównego
	time_2b3 = @elapsed begin
		A, C, Y = LU_decomposition(n, l, diag, sub, sup; pivot=true)
		x_2b3 = LU_solve(n, l, copy(A), copy(C), copy(Y), b; pivot=true)
	end
	norm_2b3 = norm(x_true - x_2b3) / norm(x_true)
	write_vector(file_2b3, x_2b3; norm=norm_2b3)

	# zapis norm
	open(norms_file, "a") do io
		@printf(io, "%d & %.10g & %.10g & %.10g & %.10g \\\\\n", n, norm_1a, norm_1b, norm_2a3, norm_2b3)
	end

	# zapis czasów
	open(times_file, "a") do io
		@printf(io, "%d & %.10g & %.10g & %.10g & %.10g \\\\\n", n, time_1a, time_1b, time_2a3, time_2b3)
	end

	# zapis danych do wykresu
	if n != 16
		push!(ns, n_from_dir)
		push!(t1a_list, time_1a)
		push!(t1b_list, time_1b)
		push!(t2a3_list, time_2a3)
		push!(t2b3_list, time_2b3)
	end
end

# zamykanie tabel w plikach
open(norms_file, "a") do io
	println(io, "\\end{tabular}")
end
open(times_file, "a") do io
	println(io, "\\end{tabular}")
end

# tworzenie wykresu
println("Tworzenie wykresu")
plot(ns, t1a_list, label="Gauss bez częściowego wyboru", marker=:o, lw=2, grid=true)
plot!(ns, t1b_list, label="Gauss z częściowym wyborem", marker=:o, lw=2)
plot!(ns, t2a3_list, label="LU bez częściowego wyboru", marker=:o, lw=2)
plot!(ns, t2b3_list, label="LU z częściowym wyborem", marker=:o, lw=2)

xlabel!("Rozmiar macierzy n")
ylabel!("Czas [s]")
title!("Czasy wykonania metod")
savefig(joinpath(output_dir, "times_plot.png"))