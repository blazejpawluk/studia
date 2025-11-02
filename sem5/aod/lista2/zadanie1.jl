using JuMP, GLPK
include("input.jl")
include("model.jl")

# wczytywanie danych z pliku
filename = "data/1.txt"
mode, n, dim, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x  = createModel(mode, n, dim, costs, A, b)

# wypisywanie wyników
# plan zakupu
println("Plan zakupu i dostaw paliwa:")
for firma in 1:3
	println("Firma $firma:")
	for lotnisko in 1:4
		println("\tLotnisko $lotnisko: $(value(x[(firma-1) * 4 + lotnisko])) galonów")
	end
	println()
end

# punkt a
println("\na) Minimalny łączny koszt: $(objective_value(model))\$")

# punkt b
println("\nb) Firmy, ktore nie dostarczaja wcale paliwa:")
for firma in 1:3
	sum = 0
	for lotnisko in 1:4
		sum += value(x[(firma-1) * 4 + lotnisko])
	end
	
	if sum == 0
		println("Firma $firma")
	end
end

# punkt c
println("\nc) Firmy, które wyczerpały możliwości dostaw paliwa:")
for firma in 1:3
	sum = 0
	for lotnisko in 1:4
		sum += value(x[(firma-1) * 4 + lotnisko])
	end

	if sum == -b[firma]
		println("Firma $firma")
	end
end