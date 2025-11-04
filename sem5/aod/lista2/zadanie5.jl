using JuMP, GLPK

function parseInput(filename)
	# wczytywanie danych
	lines = readlines(filename)

	D = parse(Int, lines[1])
	Z = parse(Int, lines[2])
	n = D*Z

	l = []
	u = []
	for i in 1:n
		line = split(lines[2+i])
		append!(l, parse(Int, line[1]))
		append!(u, parse(Int, line[2]))
	end

	z = []
	for i in 1:Z
		append!(z, parse(Int, lines[2+n+i]))
	end
	
	d = []
	for i in 1:D
		append!(d, parse(Int, lines[2+n+Z+i]))
	end

	# przetwarzanie danych
	costs = [1 for i in 1:n]

	A = []
	b = []
	for i in 1:n
		Atemp = [0 for i in 1:n]
		Atemp[i] = 1
		append!(A, Atemp)
		append!(b, l[i])

		Atemp = [0 for i in 1:n]
		Atemp[i] = -1
		append!(A, Atemp)
		append!(b, -u[i])
	end

	for j in 1:Z
		Atemp = [0 for i in 1:n]
		for i in 1:D
			Atemp[(j-1)*Z + i] = 1
		end
		append!(A, Atemp)
		append!(b, z[j])
	end

	for i in 1:D
		Atemp = [0 for i in 1:n]
		for j in 1:Z
			Atemp[(j-1)*Z + i] = 1
		end
		append!(A, Atemp)
		append!(b, d[i])
	end

	A = reshape(A, n, length(b))'

	return "min", n, costs, A, b
end

function createModelInt(mode, n, costs, A, b)
	model = Model(GLPK.Optimizer)
	@variable(model, x[1:n] >= 0, Int)

	@objective(model, Min, sum(costs[j] * x[j] for j in 1:n))
	
	for i in 1:size(A, 1)
		@constraint(model, sum(A[i,j] * x[j] for j in 1:n) >= b[i])
	end

	optimize!(model)

	return model, x
end

# wczytywanie danych z pliku
filename = "data/5.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelInt(mode, n, costs, A, b)

# wypisywanie wyników
println("Rozłożenie radiowozów:")
sum = [0 for i in 1:3]
for zmiana in 1:3
	println("Zmiana $zmiana:")
	for dzielnica in 1:3
		println("\tDzielnica $dzielnica: $(value(x[(zmiana-1)*3 + dzielnica]))")
		sum[zmiana] += value(x[(zmiana-1)*3 + dzielnica])
	end
end
println("Przepływ: $(objective_value(model))")

println("\nLiczba radiowozów: $(maximum(sum))")