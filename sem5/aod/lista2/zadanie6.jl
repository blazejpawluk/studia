using JuMP, GLPK
include("model.jl")

# parametry zgodne z opisem ze sprawozdania (6.1.1)
m = 0
n = 0
k = 0
N = 0
K = []

function Kcontains(i,j)
	for index in 1:N
		if K[index,1] == i && K[index,2] == j
			return true
		end
	end
	return false
end

function parseInput(filename)
	# wczytywanie danych
	println("Wczytywanie danych...")
	lines = readlines(filename)

	global n = parse(Int, lines[1])
	global m = parse(Int, lines[2])
	println("n=$n, m=$m")

	global k = parse(Int, lines[3])
	println("k=$k")

	global N = parse(Int, lines[4])
	println("N=$N")

	global K = []
	for i in 1:N
		line = split(lines[4+i])
		append!(K, parse(Int, line[1]))
		append!(K, parse(Int, line[2]))
	end
	global K = reshape(K, 2, N)'
	println("K=$K")

	println("Dane wczytane.")

	# przetwarzanie danych
	println("Przetwarzanie danych...")

	mode = "min"
	nModel = n*m

	costs = []
	for i in 1:n
		for j in 1:m
			if Kcontains(i,j)
				append!(costs, prevfloat(typemax(Float64)))
			else
				append!(costs, 1)
			end
		end
	end
	println("costs=$costs")

	A = []
	b = [1 for i in 1:N]
	for index in 1:N
		i = K[index, 1]
		j = K[index, 2]
		Atemp = [0 for i in 1:nModel]

		# kamera widzi kwadrat
		# for a in max(1, i-k):min(n, i+k)
		# 	for b in max(1, j-k):min(m, j+k)
		# 		Atemp[(a-1)*m + b] = 1
		# 	end
		# end

		# kamera widzi plus
		for a in max(1, i-k):min(n, i+k)
			Atemp[(a-1)*m + j] = 1
		end
		for b in max(1, j-k):min(m, j+k)
			Atemp[(i-1)*m + b] = 1
		end

		append!(A, Atemp)
	end
	A = reshape(A, nModel, length(b))'

	println("A=$A")
	println("b=$b")

	println("Dane przetworzone.")

	return mode, nModel, costs, A, b
end

# wczytywanie danych
# dane w pliku w formacie
# n
# m
# k
# N
# K11 K12
# K21 K22
# ...
# KN1 KN2

# k = 1
filename = "data/6-1.txt"
mode, nModel, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelFloat(mode, nModel, costs, A, b)

# wypisanie danych
println()
for j in 1:m
	print("+---")
end
print("+\n")
for i in 1:n
	for j in 1:m
		if value(x[(i-1) * m + j]) == 1
			print("| • ")
		elseif Kcontains(i,j)
			print("| ■ ")
		else
			print("|   ")
		end
	end
	print("|\n")
	for j in 1:m
		print("+---")
	end
	print("+\n")
end
println()

# k = 2
filename = "data/6-2.txt"
mode, nModel, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelFloat(mode, nModel, costs, A, b)

# wypisanie danych
println()
for j in 1:m
	print("+---")
end
print("+\n")
for i in 1:n
	for j in 1:m
		if value(x[(i-1) * m + j]) == 1
			print("| • ")
		elseif Kcontains(i,j)
			print("| ■ ")
		else
			print("|   ")
		end
	end
	print("|\n")
	for j in 1:m
		print("+---")
	end
	print("+\n")
end
println()