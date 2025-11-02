using JuMP, GLPK
include("input.jl")
include("model.jl")

# wczytywanie danych z pliku
filename = "data/2.txt"
mode, n, costs, A, b = parseInput(filename)

# tworzenie modelu
model, x  = createModel(mode, n, costs, A, b)

# wypisywanie wyników
# plan produkcji
println("Plan produkcji:")
for p in 1:4
	println("Produkt P$p: $(value(x[p]))kg")
end

# zysk
println("\nZysk ze sprzedaży przy takiej produkcji: $(objective_value(model))\$")