# funkcja przyjmuje niezbędne dane problemu LP i zwraca zoptymalizowany model problemu

using JuMP, GLPK

function createModel(mode, n, costs, A, b)
	model = Model(GLPK.Optimizer)
	@variable(model, x[1:n] >= 0)

	if mode == "max"
		@objective(model, Max, sum(costs[j] * x[j] for j in 1:n))
	else
		@objective(model, Min, sum(costs[j] * x[j] for j in 1:n))
	end

	for i in 1:size(A, 1)
		if mode == "max"
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) <= b[i])
		else
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) >= b[i])
		end
	end

	optimize!(model)

	return model, x
end