using JuMP, GLPK
include("model.jl")

# parametry zgodne z opisem ze sprawozdania (4.1.1)
n = 0
m = 0
E = []
io = 0
jo = 0
T = 0

function parseInput(filename)
	# wczytywanie danych z pliku
	println("Wczytywanie pliku...")
	lines = readlines(filename)

	global n = parse(Int, lines[1])
	global m = parse(Int, lines[2])
	println("n=$n, m=$m")

	global E = [(0,0,0.0,0.0) for i in 1:m]
	for i in 1:m
		line = split(lines[2+i])
		u = parse(Int, line[1])
		v = parse(Int, line[2])
		c = parse(Float64, line[3])
		t = parse(Float64, line[4])
		E[i] = (u,v,c,t)
	end
	println("E=$E")

	global io = parse(Int, lines[3+m])
	global jo = parse(Int, lines[4+m])
	println("io=$io, jo=$jo")

	global T = parse(Float64, lines[5+m])
	println("T=$T")

	println("Dane wczytane.\n")

	# przetwarzanie danych
	println("Przetwarzanie danych...")

	mode = "min"

	costs = []
	for i in 1:m
		(u,v,c,t) = E[i]
		append!(costs, c)
	end
	println("costs=$costs")

	A = []
	b = []
	for i in 1:m
		(u,v,c,t) = E[i]
		append!(A, -t)
	end
	append!(b, -T)

	for j in 1:n
		for i in 1:m
			(u,v,c,t) = E[i]
			if u == j
				append!(A, 1)
			elseif v == j
				append!(A, -1)
			else
				append!(A, 0)
			end
		end
		
		if j == io
			append!(b, 1)
		elseif j == jo
			append!(b, -1)
		else
			append!(b, 0)
		end
	end

	A = reshape(A, m, length(b))'
	println("A=$A")
	println("b=$b")

	println("Dane przetworzone.\n")

	return mode, m, costs, A, b
end

# dane w pliku w formacie
# n
# m
# u1 v1 c1 t1
# u2 v2 c2 t2
# ...
# um vm cm tm
# io
# jo
# T

# punkt a
# wczytywanie danych
filename = "data/4a.txt"
mode, m, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelBool(mode, m, costs, A, b)

# wypisywanie wyniku
println("\na)\nOptymalna ścieżka:")
cost = 0
time = 0
for i in 1:m
	if value(x[i]) == 1
		(u,v,c,t) = E[i]
		println("($u, $v, $c, $t)")
		global cost += c
		global time += t
	end
end
println("Koszt tej trasy: $cost")
println("Czas tej trasy: $time\n")

# punkt b
# wczytywanie danych
filename = "data/4b.txt"
mode, m, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelBool(mode, m, costs, A, b)

# wypisywanie wyniku
println("\nb)\nOptymalna ścieżka:")
cost = 0
time = 0
for i in 1:m
	if value(x[i]) == 1
		(u,v,c,t) = E[i]
		println("($u, $v, $c, $t)")
		global cost += c
		global time += t
	end
end
println("Koszt tej trasy: $cost")
println("Czas tej trasy: $time\n")

# punkt c
# wczytywanie danych
filename = "data/4b.txt"
mode, m, costs, A, b = parseInput(filename)

# tworzenie modelu
# model jak w poprzednich zadaniach na liczbach zmiennoprzecinkowych
model, x = createModelFloat(mode, m, costs, A, b)

println("\nc)\nOptymalna ścieżka:")
cost = 0
time = 0
for i in 1:m
	if value(x[i]) > 0
		(u,v,c,t) = E[i]
		println("$(value(x[i])): ($u, $v, $c, $t)")
		global cost += value(x[i])*c
		global time += value(x[i])*t
	end
end
println("Koszt tej trasy: $cost")
println("Czas tej trasy: $time\n")

# punkt d
# wczytywanie danych
filename = "data/4b.txt"
mode, m, costs, A, b = parseInput(filename)

# pozbycie się oganiczenia na czasy przejazdu
A = A[2:end, :]
b = b[2:end]

# tworzenie modelu
# model jak w poprzednich zadaniach na liczbach zmiennoprzecinkowych
model, x = createModelFloat(mode, m, costs, A, b)

println("\nd)\nOptymalna ścieżka:")
cost = 0
time = 0
for i in 1:m
	if value(x[i]) > 0
		(u,v,c,t) = E[i]
		println("$(value(x[i])): ($u, $v, $c, $t)")
		global cost += value(x[i])*c
		global time += value(x[i])*t
	end
end
println("Koszt tej trasy: $cost")
println("Czas tej trasy: $time\n")