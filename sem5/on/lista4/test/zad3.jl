# Błażej Pawluk

include("../src/ilorazyRoznicowe.jl")
include("../src/warNewton.jl")
include("../src/naturalna.jl")
using .IlorazyRoznicowe
using .WarNewton
using .Naturalna

# function test(nazwa, x, f, expected)
# 	println("TEST: ", nazwa)
# 	println("Węzły: x = ", x)
# 	println("Wartości: f = ", f)
# 	println()

# 	fx = ilorazyRoznicowe(x, f)
# 	nat = naturalna(x, fx)
# 	println(" Naturalna: ", nat)
# 	println("Oczekiwane: ", expected)
# 	println()
# 	println()
# end

# println("=" ^ 50)
# println("TESTY NATURALNA")
# println("=" ^ 50)
# println()

# f1(x) = 2x + 3
# x1 = [0.0, 1.0, 2.0]
# fx1 = [f1(x) for x in x1]
# expected1 = [3.0, 2.0, 0.0]
# test("Funkcja liniowa f(x) = 2x + 3", 
# 	x1, fx1, expected1)

# f2(x) = x^2
# x2 = [0.0, 1.0, 2.0]
# fx2 = [f2(xi) for xi in x2]
# expected2 = [0.0, 0.0, 1.0]
# test("Funkcja kwadratowa f(x) = x^2",
# 	x2, fx2, expected2)

# f3(x) = 5.0
# x3 = [1.0, 2.0, 3.0]
# fx3 = [f3(xi) for xi in x3]
# expected3 = [5.0, 0.0, 0.0]
# test("Funkcja stała f(x) = 5",
# 	x3, fx3, expected3)

# x4 = [1.0, 2.0, 4.0, 6.0]
# fx4 = [1.0, 4.0, 8.0, 14.0]
# expected4 = [0.0, 0.0, 0.0, 0.0]
# test("Przykład z wykładu",
# 	x4, fx4, expected4)
	
# println("=" ^ 50)

x = [-1.0, 0.0, 1.0, 2.0]
fx = [-1.0, 0.0, -1.0, 2.0]
ilo = ilorazyRoznicowe(x, fx)
nat = naturalna(x, ilo)
println(nat)