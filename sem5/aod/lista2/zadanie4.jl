using JuMP, GLPK
include("model.jl")

E = [] # potrzebne do wypisania wyniku
function parseInput(filename)
	lines = readlines(filename)

	# czytanie pliku
	n = parse(Int, lines[1])
	io = parse(Int, lines[2])
	jo = parse(Int, lines[3])
	T = parse(Int, lines[4])
	m = parse(Int, lines[5])
	global E = [(0,0,0,0) for i in 1:m]
	for l in 6:5+m
		line = split(lines[l])
		E[l-5] = (parse(Int, line[1]), parse(Int, line[2]), parse(Int, line[3]), parse(Int, line[4]))
	end

	# przetwarzanie danych
	costs = Int[]
	A = Int[]
	for i in 1:m
		u,v,c,t = E[i]
		append!(costs, c)
		append!(A, -t)
	end

	b = Int[-T]
	for j in 1:n
		if j == io
			append!(b, 1)
		elseif j == jo
			append!(b, -1)
		else
			append!(b, 0)
		end

		for i in 1:m
			u,v,c,t = E[i]
			if u == j
				append!(A, 1)
			elseif v == j
				append!(A, -1)
			else
				append!(A, 0)
			end
		end
	end

	A = reshape(A, m, n+1)'

	return "min", m, costs, A, b
end

function createModelInt(mode, n, costs, A, b)
	model = Model(GLPK.Optimizer)
	@variable(model, 0 <= x[1:n] <= 1, Int)

	@objective(model, Min, sum(costs[j] * x[j] for j in 1:n))
	
	for i in 1:size(A, 1)
		@constraint(model, sum(A[i,j] * x[j] for j in 1:n) >= b[i])
	end

	optimize!(model)

	return model, x
end

# punkt a
filename = "data/4a.txt"
mode, n, costs, A, b = parseInput(filename)

model, x = createModelInt(mode, n, costs, A, b)

println("a)\nOptymalna ścieżka:")
koszt = 0
czas = 0
for i in 1:n
	if value(x[i]) == 1
		u,v,c,t = E[i]
		println("($u, $v, $c, $t)")
		global koszt += c
		global czas += t
	end
end
println("Koszt tej trasy: $koszt")
println("Czas tej trasy: $czas")

# punkt b
filename = "data/4b.txt"
mode, n, costs, A, b = parseInput(filename)

model, x = createModelInt(mode, n, costs, A, b)

println("\nb)\nOptymalna ścieżka:")
koszt = 0
czas = 0
for i in 1:n
	if value(x[i]) == 1
		u,v,c,t = E[i]
		println("($u, $v, $c, $t)")
		global koszt += c
		global czas += t
	end
end
println("Koszt tej trasy: $koszt")
println("Czas tej trasy: $czas")

# punkt c
filename = "data/4b.txt"
mode, n, costs, A, b = parseInput(filename)

# model jak w poprzednich zadaniach na liczbach zmiennoprzecinkowych
model, x = createModel(mode, n, costs, A, b)

println("\nc)\nOptymalna ścieżka:")
koszt = 0
czas = 0
for i in 1:n
	if value(x[i]) > 0
		u,v,c,t = E[i]
		println("$(value(x[i])): ($u, $v, $c, $t)")
		global koszt += value(x[i])*c
		global czas += value(x[i])*t
	end
end
println("Koszt tej trasy: $koszt")
println("Czas tej trasy: $czas")

# punkt d
filename = "data/4b.txt"
mode, n, costs, A, b = parseInput(filename)

# pozbycie się oganiczenia na czasy przejazdu
A = A[2:end, :]
b = b[2:end]

# model jak w poprzednich zadaniach na liczbach zmiennoprzecinkowych
model, x = createModel(mode, n, costs, A, b)

println("\nd)\nOptymalna ścieżka:")
koszt = 0
czas = 0
for i in 1:n
	if value(x[i]) > 0
		u,v,c,t = E[i]
		println("$(value(x[i])): ($u, $v, $c, $t)")
		global koszt += value(x[i])*c
		global czas += value(x[i])*t
	end
end
println("Koszt tej trasy: $koszt")
println("Czas tej trasy: $czas")