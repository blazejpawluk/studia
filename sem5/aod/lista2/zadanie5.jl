using JuMP, GLPK
include("model.jl")

# parametry zgodne z opisem ze sprawozdania (5.1.1)
Z = 0
D = 0
l = []
u = []
z = []
d = []

function parseInput(filename)
	# wczytywanie danych
	println("Wczytywanie pliku...")
	lines = readlines(filename)

	global Z = parse(Int, lines[1])
	global D = parse(Int, lines[2])
	println("Z=$Z, D=$D")

	for i in 1:Z
		line = split(lines[2+i])
		for j in 1:D
			append!(l, parse(Int, line[j]))
		end
	end
	global l = reshape(l, D, Z)'
	println("l=$l")

	for i in 1:Z
		line = split(lines[2+Z+i])
		for j in 1:D
			append!(u, parse(Int, line[j]))
		end
	end
	global u = reshape(u, D, Z)'
	println("u=$u")

	line = split(lines[3+2*Z])
	for i in 1:Z
		append!(z, parse(Int, line[i]))
	end
	println("z=$z")

	line = split(lines[4+2*Z])
	for j in 1:D
		append!(d, parse(Int, line[j]))
	end
	println("d=$d")

	println("Dane wczytane.\n")

	# przetwarzanie danych
	println("Przetwarzanie danych...")

	mode = "min"
	n = Z*D

	costs = [1 for i in 1:n]
	println("costs=$costs")

	A = []
	b = []
	for i in 1:Z
		for j in 1:D
			Atemp = [0 for i in 1:n]
			Atemp[(i-1)*D + j] = 1
			append!(A, Atemp)
			append!(b, l[i,j])

			Atemp[(i-1)*D + j] = -1
			append!(A, Atemp)
			append!(b, -u[i,j])
		end
	end

	for i in 1:Z
		Atemp = [0 for i in 1:n]
		for j in 1:D
			Atemp[(i-1)*D + j] = 1
		end

		append!(A, Atemp)
		append!(b, z[i])
	end

	for j in 1:D
		Atemp = [0 for i in 1:n]
		for i in 1:Z
			Atemp[(i-1)*D + j] = 1
		end

		append!(A, Atemp)
		append!(b, d[j])
	end
	A = reshape(A, n, length(b))'

	println("A=$A")
	println("b=$b")

	println("Dane przetworzone.")

	return mode, n, costs, A, b
end

# wczytywanie danych z pliku
# dane w pliku w formacie
# Z
# D
# l11 l12 ... l1D
# l21 l22 ... l2D
# ...
# lZ1 lZ2 ... lZD
# u11 u12 ... u1D
# u21 u22 ... u2D
# ...
# uZ1 uZ2 ... uZD
# z1 z2 ... zZ
# d1 d2 ... dD
filename = "data/5.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelFloat(mode, n, costs, A, b)

# wypisywanie wyników
println("\nRozłożenie radiowozów:")
sum = [0 for i in 1:Z]
for i in 1:Z
	println("Zmiana $i:")
	for j in 1:D
		println("\tDzielnica $j: $(value(x[(i-1)*3 + j]))")
		sum[i] += value(x[(i-1)*3 + j])
	end
end
println("Przepływ: $(objective_value(model))")

println("\nLiczba radiowozów: $(maximum(sum))")

# wypisywanie do sprawozdania
println("\nSPRAWOZDANIE:")
print("        Dzielnica ")
for j in 1:D
	print("&\$p_$j\$ ")
end
println("\\\\\n        \\hline")
for i in 1:Z
	print("        Zmiana $i ")
	for j in 1:D
		print("&$(value(x[(i-1)*D + j])) ")
	end
	print("\\\\\n")
end