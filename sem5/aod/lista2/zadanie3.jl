using JuMP, GLPK
include("model.jl")

# parametry zgodne z opisem ze sprawozdania (3.1.1)
K = 0
N = 0
c = []
a = []
o = []
d = []
M = 0
k = 0
m0 = 0

function parseInput(filename)
	# wczytywanie danych z pliku
	println("Wczytywanie pliku...")
	lines = readlines(filename)

	global K = parse(Int, lines[1])
	println("K=$K")

	global N = parse(Int, lines[2])
	println("N=$N")

	line = split(lines[3])
	for i in 1:K
		append!(c, parse(Float64, line[i]))
	end
	println("c=$c")

	line = split(lines[4])
	for i in 1:K
		append!(a, parse(Int, line[i]))
	end
	println("a=$a")

	line = split(lines[5])
	for i in 1:K
		append!(o, parse(Float64, line[i]))
	end
	println("o=$o")

	line = split(lines[6])
	for i in 1:K
		append!(d, parse(Int, line[i]))
	end
	println("d=$d")

	global M = parse(Int, lines[7])
	println("M=$M")

	global k = parse(Float64, lines[8])
	println("k=$k")

	global m0 = parse(Int, lines[9])
	println("m0=$m0")

	println("Dane wczytane.\n")

	# przetwarzanie danych
	println("Przetwarzanie danych...")

	mode = "min"
	n = 3*K

	costs = []
	append!(costs, c)
	append!(costs, o)
	append!(costs, [k for i in 1:K])
	println("costs=$costs")

	A = []
	b = []
	for i in 1:K
		Atemp = [0 for i in 1:n]
		Atemp[i] = -1
		append!(A, Atemp)
		append!(b, -N)

		Atemp[i] = 0
		Atemp[K+i] = -1
		append!(A, Atemp)
		append!(b, -a[i])

		Atemp[K+i] = 0
		Atemp[2*K+i] = -1
		append!(A, Atemp)
		append!(b, -M)

		Atemp[2*K+i] = 0
		Atemp[i] = 1
		Atemp[K+i] = 1
		Atemp[2*K+i] = -1
		if i == 1
			append!(b, d[i] - m0)
		else
			Atemp[2*K+i-1] = 1
			append!(b, d[i])
		end
		append!(A, Atemp)
	end
	A = reshape(A, n, length(b))'
	println("A=$A")
	println("b=$b")

	println("Dane przetworzone.\n")

	return mode, n, costs, A, b
end

# wczytywanie danych z pliku
# dane w pliku w formacie
# K
# N
# c1 c2 ... cK
# a1 a2 ... aK
# o1 o2 ... oK
# d1 d2 ... dK
# M
# k
# m0
filename = "data/3.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x  = createModelFloat(mode, n, costs, A, b)

# wypisywanie wyników
# produkcja normalna
println("Produkcja normalna:")
for i in 1:K
	println("\tOkres $i: $(value(x[i]))")
end

# produkcja ponadwymiarowa
println("Produkcja ponadwymiarowa:")
for i in 1:K
	println("\tOkres $i: $(value(x[K+i]))")
end

# stan magazynu
println("Stan magazynu:")
for i in 1:K
	println("\tOkres $i: $(value(x[2*K+i]))")
end

# punkt a
println("\na) Minimalny koszt produkcji i magazynowania towaru: $(objective_value(model))\$")

# punkt b
println("\nb) Okresy z ponadwymiarową produkcją:")
for i in 1:K
	if value(x[K+i]) > 0
		println("\tOkres $i: $(value(x[K+i]))")
	end
end

# punkt c
println("\nc) Okresy z pełnym magazynem:")
for i in 1:K
	if value(x[2*K+i]) == 70
		println("\tOkres $i")
	end
end

# wypisywanie do sprawozdania
println("\nSPRAWOZDANIE:")
print("        Okres ")
for i in 1:K
	print("&$i ")
end
println("\\\\\n        \\hline")
print("        Produkcja normalna ")
for i in 1:K
	print("& $(value(x[i])) ")
end
print("\\\\\n        Produkcja ponadwymiarowa ")
for i in 1:K
	print("& $(value(x[K+i])) ")
end
print("\\\\\n        Stan magazynu ")
for i in 1:K
	print("& $(value(x[2*K+i])) ")
end
print("\\\\\n")