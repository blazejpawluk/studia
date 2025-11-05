using JuMP, GLPK

function createModelFloat(mode, n, costs, A, b)
	println("Tworzenie modelu...")
	model = Model(GLPK.Optimizer)

	println("Zmienne decyzyjne.")
	@variable(model, x[1:n] >= 0)

	println("Tryb i funkcja kosztu.")
	if mode == "max"
		@objective(model, Max, sum(costs[j] * x[j] for j in 1:n))
	else
		@objective(model, Min, sum(costs[j] * x[j] for j in 1:n))
	end

	println("Ograniczenia.")
	for i in 1:size(A, 1)
		if mode == "max"
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) <= b[i])
		else
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) >= b[i])
		end
	end

	println("Optymalizacja.")
	optimize!(model)

	println("Model stworzony.")

	return model, x
end

function createModelInt(mode, n, costs, A, b)
	println("Tworzenie modelu...")
	model = Model(GLPK.Optimizer)

	println("Zmienne decyzyjne.")
	@variable(model, x[1:n] >= 0, Int)

	println("Tryb i funkcja kosztu.")
	if mode == "max"
		@objective(model, Max, sum(costs[j] * x[j] for j in 1:n))
	else
		@objective(model, Min, sum(costs[j] * x[j] for j in 1:n))
	end

	println("Ograniczenia.")
	for i in 1:size(A, 1)
		if mode == "max"
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) <= b[i])
		else
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) >= b[i])
		end
	end

	println("Optymalizacja.")
	optimize!(model)

	println("Model stworzony.")

	return model, x
end

function createModelBool(mode, n, costs, A, b)
	println("Tworzenie modelu...")
	model = Model(GLPK.Optimizer)

	println("Zmienne decyzyjne.")
	@variable(model, 0 <= x[1:n] <= 1, Int)

	println("Tryb i funkcja kosztu.")
	if mode == "max"
		@objective(model, Max, sum(costs[j] * x[j] for j in 1:n))
	else
		@objective(model, Min, sum(costs[j] * x[j] for j in 1:n))
	end

	println("Ograniczenia.")
	for i in 1:size(A, 1)
		if mode == "max"
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) <= b[i])
		else
			@constraint(model, sum(A[i,j] * x[j] for j in 1:n) >= b[i])
		end
	end

	println("Optymalizacja.")
	optimize!(model)

	println("Model stworzony.")

	return model, x
end