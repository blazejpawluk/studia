# Błażej Pawluk, 279738
# plik do generowania danych eksperymentów z wygenerowanych macierzy

include("src/blocksys.jl")
include("src/matrixgen.jl")

using .blocksys
using .matrixgen
using LinearAlgebra
using Plots
using Printf
using Statistics

# folder na wyniki
output_dir = "output/random"
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

# tablice na dane do wykresu (ŚREDNIE)
ns = Int[]
t1a_list = Float64[]
t1b_list = Float64[]
t2a3_list = Float64[]
t2b3_list = Float64[]

# badane rozmiary macierzy
n_list = [10000, 50000, 100000, 500000, 750000, 1000000]

# parametry bloków
l = 4
ck = 10.0

# liczba losowań
samples = 10

# przetwarzanie danych
for n in n_list
	println("Przetwarzanie danych dla n = ", n)

	# katalog wyjściowy
	out_n_dir = joinpath(output_dir, string(n))
	isdir(out_n_dir) || mkdir(out_n_dir)

	# tablice pomocnicze na czasy i normy
	norms_1a = Float64[]
	norms_1b = Float64[]
	norms_2a3 = Float64[]
	norms_2b3 = Float64[]

	times_1a = Float64[]
	times_1b = Float64[]
	times_2a3 = Float64[]
	times_2b3 = Float64[]

	for k in 1:samples
		println("  Próba ", k, "/", samples)

		# tymczasowy plik macierzy
		A_file = joinpath(out_n_dir, "A_tmp.txt")

		# generowanie macierzy
		blockmat(n, l, ck, A_file)

		# wczytanie danych (bez zmiany reszty programu)
		n_read, l_read, diag, sub, sup = read_matrix(A_file)
		b = calc_b(n_read, l_read, diag, sub, sup)
		x_true = ones(Float64, n_read)

		# ZADANIE 1 - Gauss
		time_1a = @elapsed begin
			x_1a = gauss(n_read, l_read, diag, sub, sup, b; pivot=false)
		end
		push!(norms_1a, norm(x_true - x_1a) / norm(x_true))
		push!(times_1a, time_1a)

		time_1b = @elapsed begin
			x_1b = gauss(n_read, l_read, diag, sub, sup, b; pivot=true)
		end
		push!(norms_1b, norm(x_true - x_1b) / norm(x_true))
		push!(times_1b, time_1b)

		# ZADANIE 2+3 - LU
		time_2a3 = @elapsed begin
			A, C, Y = LU_decomposition(n_read, l_read, diag, sub, sup; pivot=false)
			x_2a3 = LU_solve(n_read, l_read, copy(A), copy(C), copy(Y), b; pivot=false)
		end
		push!(norms_2a3, norm(x_true - x_2a3) / norm(x_true))
		push!(times_2a3, time_2a3)

		time_2b3 = @elapsed begin
			A, C, Y = LU_decomposition(n_read, l_read, diag, sub, sup; pivot=true)
			x_2b3 = LU_solve(n_read, l_read, copy(A), copy(C), copy(Y), b; pivot=true)
		end
		push!(norms_2b3, norm(x_true - x_2b3) / norm(x_true))
		push!(times_2b3, time_2b3)
	end

	# średnie wartości
	mean_norm_1a  = mean(norms_1a)
	mean_norm_1b  = mean(norms_1b)
	mean_norm_2a3 = mean(norms_2a3)
	mean_norm_2b3 = mean(norms_2b3)

	mean_time_1a  = mean(times_1a)
	mean_time_1b  = mean(times_1b)
	mean_time_2a3 = mean(times_2a3)
	mean_time_2b3 = mean(times_2b3)

	# zapis norm
	open(norms_file, "a") do io
		@printf(io, "%d & %.10g & %.10g & %.10g & %.10g \\\\\n",
		        n, mean_norm_1a, mean_norm_1b, mean_norm_2a3, mean_norm_2b3)
	end

	# zapis czasów
	open(times_file, "a") do io
		@printf(io, "%d & %.10g & %.10g & %.10g & %.10g \\\\\n",
		        n, mean_time_1a, mean_time_1b, mean_time_2a3, mean_time_2b3)
	end

	# dane do wykresu (średnie)
	push!(ns, n)
	push!(t1a_list, mean_time_1a)
	push!(t1b_list, mean_time_1b)
	push!(t2a3_list, mean_time_2a3)
	push!(t2b3_list, mean_time_2b3)
end

# zamykanie tabel
open(norms_file, "a") do io
	println(io, "\\end{tabular}")
end

open(times_file, "a") do io
	println(io, "\\end{tabular}")
end

# tworzenie wykresu (ŚREDNIE)
println("Tworzenie wykresu")
plot(ns, t1a_list, label="Gauss bez częściowego wyboru", marker=:o, lw=2, grid=true)
plot!(ns, t1b_list, label="Gauss z częściowym wyborem", marker=:o, lw=2)
plot!(ns, t2a3_list, label="LU bez częściowego wyboru", marker=:o, lw=2)
plot!(ns, t2b3_list, label="LU z częściowym wyborem", marker=:o, lw=2)

xlabel!("Rozmiar macierzy n")
ylabel!("Czas [s]")
title!("Średnie czasy wykonania metod")
savefig(joinpath(output_dir, "times_plot.png"))
