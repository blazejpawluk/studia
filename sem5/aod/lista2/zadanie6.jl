using JuMP, GLPK

containers = []
m = 0
n = 0
function parseInput(filename)
	lines = readlines(filename)

	global m = parse(Int, lines[1])
	global n = parse(Int, lines[2])
	k = parse(Int, lines[3])
	
	K = parse(Int, lines[4])
	costs = [1.0 for i in 1:m*n]
	for i in 1:K
		line = split(lines[4+i])
		u = parse(Int, line[1])
		v = parse(Int, line[2])
		costs[(u-1) * m + v] = prevfloat(typemax(Float64))
		append!(containers, [u,v])
	end
	global containers = reshape(containers, 2, K)'
	
	A = []
	b = [1 for i in 1:K]
	for x in 1:K
		I = containers[x,1]
		J = containers[x,2]
		
		Atemp = [0 for i in 1:m*n]
		# for i in max(1, I-k):min(n, I+k)
		# 	for j in max(1, J-k):min(n, J+k)
		# 		Atemp[(i-1) * m + j] = 1
		# 	end
		# end

		for i in max(1, I-k):min(n, I+k)
			Atemp[(i-1) * m + J] = 1
		end
		for j in max(1, J-k):min(n, J+k)
			Atemp[(I-1) * m + j] = 1
		end
		
		append!(A, Atemp)
	end
	A = reshape(A, m*n, K)'

	return "min", m*n, costs, A, b
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

# wczytywanie danych
filename = "data/6.txt"
mode, N, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x = createModelInt(mode, N, costs, A, b)

function f(i,j)
	K = size(containers, 1)
	for x in 1:K
		if containers[x,1] == i && containers[x,2] == j
			return true
		end
	end

	return false
end

# wypisanie danych
for i in 1:n
	for j in 1:m
		if value(x[(i-1) * m + j]) == 1
			print("O")
		elseif f(i,j)
			print("K")
		else
			print("-")
		end
	end
	print("\n")
end