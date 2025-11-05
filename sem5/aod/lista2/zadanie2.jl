using JuMP, GLPK
include("model.jl")

# parametry zgodne z opisem ze sprawozdania (2.1.1)
P = 0
M = 0
s = []
m = []
k = []
t = []
p = []
o = []

function parseInput(filename) 
	# wczytywanie danych z pliku
	println("Wczytywanie pliku...")
	lines = readlines(filename)

	global P = parse(Int, lines[1])
	global M = parse(Int, lines[2])
	println("P=$P, M=$M")

	line = split(lines[3])
	for i in 1:P
		append!(s, parse(Float64, line[i]))
	end
	println("s=$s")

	line = split(lines[4])
	for j in 1:M
		append!(m, parse(Float64, line[j]))
	end
	println("m=$m")

	line = split(lines[5])
	for i in 1:P
		append!(k, parse(Float64, line[i]))
	end
	println("k=$k")

	for i in 1:P
		line = split(lines[5+i])
		for j in 1:M
			append!(t, parse(Float64, line[j]))
		end
	end
	global t = reshape(t, M, P)'
	println("t=$t)")

	line = split(lines[6+P])
	for i in 1:P
		append!(p, parse(Float64, line[i]))
	end
	println("p=$p")

	line = split(lines[7+P])
	for j in 1:M
		append!(o, parse(Float64, line[j]))
	end
	println("o=$o")

	println("Dane wczytane.\n")

	# przetwarzanie danych
	println("Przetwarzanie danych...")

	mode = "max"
	n = P
	
	costs = []
	for i in 1:P
		coeff = s[i] - k[i]
		for j in 1:M
			coeff -= t[i,j] * m[j] / 60
		end
		append!(costs, coeff)
	end
	println("costs=$costs")

	A = []
	b = []
	for i in 1:P
		Atemp = [0 for i in 1:n]
		Atemp[i] = 1
		append!(A, Atemp)
		append!(b, p[i])
	end

	for j in 1:M
		for i in 1:P
			append!(A, t[i,j]/60)
		end
		append!(b, o[j])
	end
	A = reshape(A, n, length(b))'
	println("A=$A")
	println("b=$b")

	println("Dane przetworzone.\n")

	return mode, n, costs, A, b
end

# wczytywanie danych z pliku
# dane w pliku w formacie
# P
# M
# s1 s2 ... sP
# m1 m2 ... mM
# k1 k2 ... kP
# t11 t12 ... t1M
# t21 t22 ... t2M
# ...
# tP1 tP2 ... tPM
# p1 p2 ... pP
# o1 o2 ... oM
filename = "data/2.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x  = createModelFloat(mode, n, costs, A, b)

# wypisywanie wyników
# plan produkcji
println("\nPlan produkcji:")
for i in 1:P
	println("Wyrób P$i: $(value(x[i]))kg")
end

# zysk
println("\nZysk ze sprzedaży: $(objective_value(model))\$")

# wypisywanie do sprawozdania
println("\nSPRAWOZDANIE:")
print("        Wyrób ")
for i in 1:P
	print("&\$P_$i\$ ")
end
println("\\\\\n        \\hline")
print("        Wielkość produkcji ")
for i in 1:P
	print("&$(value(x[i])) ")
end
print("\\\\\n") 