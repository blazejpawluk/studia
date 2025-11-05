using JuMP, GLPK
include("model.jl")

# parametry zgodne z opisem ze sprawozdania (1.1.1)
F = 0
L = 0
d = []
z = []
c = []

function parseInput(filename)
	# wczytywanie danych z pliku
	println("Wczytywanie pliku...")
	lines = readlines(filename)

	global F = parse(Int, lines[1])
	global L = parse(Int, lines[2])
	println("F=$F, L=$L")
	
	line = split(lines[3])
	for i in 1:F
		append!(d, parse(Float64, line[i]))
	end
	println("d=$d")

	line = split(lines[4])
	for j in 1:L
		append!(z, parse(Float64, line[j]))
	end
	println("z=$z")

	for i in 1:F
		line = split(lines[4+i])
		for j in 1:L
			append!(c, parse(Float64, line[j]))
		end
	end
	println("c=$(reshape(c, L, F)')")

	println("Dane wczytane.\n")

	# przetwarzanie danych
	println("Przetwarzanie danych...")
	
	mode = "min"
	n = F*L
	
	costs = c
	global c = reshape(c, L, F)'
	println("costs=$costs")

	A = []
	b = []
	for i in 1:F
		Atemp = [0 for i in 1:n]
		for j in 1:L
			Atemp[(i-1) * L + j] = -1
		end
		append!(A, Atemp)
		append!(b, -d[i])
	end

	for j in 1:L
		Atemp = [0 for i in 1:n]
		for i in 1:F
			Atemp[(i-1) * L + j] = 1
		end
		append!(A, Atemp)
		append!(b, z[j])
	end
	A = reshape(A, n, length(b))'
	println("A=$A")
	println("b=$b")

	println("Dane przetworzone.\n")

	return mode, n, costs, A, b
end

# wczytywanie danych z pliku
# dane w pliku w formacie:
# F
# L
# d1 d2 ... dF
# z1 z2 ... zL
# c11 c12 ... c1L
# c21 c22 ... c2L
# ...
# cF1 cF2 ... cFL
filename = "data/1.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x  = createModelFloat(mode, n, costs, A, b)

# wypisywanie wyników
# plan zakupu
println("\nPlan zakupu i dostaw paliwa:")
for i in 1:F
	println("Firma $i:")
	for j in 1:L
		println("\tLotnisko $j: $(value(x[(i-1) * L + j])) galonów")
	end
	println()
end

# punkt a
println("\na) Minimalny łączny koszt: $(objective_value(model))\$")

# punkt b
println("\nb) Firmy, ktore nie dostarczaja wcale paliwa:")
for i in 1:F
	sum = 0
	for j in 1:L
		sum += value(x[(i-1) * L + j])
	end
	
	if sum == 0
		println("Firma $i")
	end
end

# punkt c
println("\nc) Firmy, które wyczerpały możliwości dostaw paliwa:")
for i in 1:F
	sum = 0
	for j in 1:L
		sum += value(x[(i-1) * L + j])
	end

	if sum == d[i]
		println("Firma $i")
	end
end

# wypisywanie do sprawozdania
println("\nSPRAWOZDANIE:")
print("        ")
for j in 1:L
	print("&Lotnisko $j ")
end
println("\\\\\n        \\hline")
for i in 1:F
	print("        Firma $i ")
	for j in 1:L
		print("&$(value(x[(i-1) * L + j])) ")
	end
	print("\\\\\n")
end