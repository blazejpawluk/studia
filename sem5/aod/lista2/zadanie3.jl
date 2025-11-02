using JuMP, GLPK
include("input.jl")
include("model.jl")

# wczytywanie danych z pliku
filename = "data/3.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x  = createModel(mode, n, costs, A, b)

# wypisywanie wyników
# produkcja normalna
println("Produkcja normalna:")
for i in 1:4
	println("\tOkres $i: $(value(x[i]))")
end

# produkcja ponadwymiarowa
println("Produkcja ponadwymiarowa:")
for i in 1:4
	println("\tOkres $i: $(value(x[4+i]))")
end

# stan magazynu
println("Stan magazynu:")
for i in 1:4
	println("\tOkres $i: $(value(x[8+i]))")
end

# punkt a
println("\na) Minimalny koszt produkcji i magazynowania produktów: $(objective_value(model))\$")

# punkt b
println("\nb) Okresy z ponadwymiarową produkcją:")
for i in 1:4
	if value(x[4+i]) > 0
		println("\tOkres $i: $(value(x[4+i]))")
	end
end

# punkt c
println("\nc) Okresy z pełnym magazynem:")
for i in 1:4
	if value(x[8+i]) == 70
		println("\tOkres $i")
	end
end