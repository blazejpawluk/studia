# Błażej Pawluk

include("../src/ilorazyRoznicowe.jl")
include("../src/warNewton.jl")
using .IlorazyRoznicowe
using .WarNewton

function test(nazwa, x, f, fun, ts)
	println("TEST: ", nazwa)
	println("Węzły: x = ", x)
	println("Wartości: f = ", f)
	println()

	fx = ilorazyRoznicowe(x, f)
	println("Ilorazy różnicowe: ", fx)
	println()

	println("Testy w węzłach:")
	for i in eachindex(x)
		val = warNewton(x, fx, x[i])
		expected = f[i]
		diff = abs(val - expected)
		println("  N($(x[i])) = $val, oczekiwane = $expected, błąd = $diff")
	end
	println()

	if fun !== nothing && !isempty(ts)
		println("Test w innych punktach:")
		for t in ts
			val = warNewton(x, fx, t)
			real = fun(t)
			diff = abs(val - real)
			println("  N($t) = $val, f($t) = $real, błąd = $diff")
		end
	end
	println()
	println()
end

println("=" ^ 50)
println("TESTY WARNEWTON")
println("=" ^ 50)
println()

f1(x) = 2x + 3
x1 = [0.0, 1.0, 2.0]
fx1 = [f1(x) for x in x1]
test("Funkcja liniowa f(x) = 2x + 3", 
	x1, fx1, f1, [0.5, 1.5, 2.5])

f2(x) = x^2
x2 = [0.0, 1.0, 2.0]
fx2 = [f2(xi) for xi in x2]
test("Funkcja kwadratowa f(x) = x^2",
	x2, fx2, f2, [0.5, 1.5, 2.5])

f3(x) = 5.0
x3 = [1.0, 2.0, 3.0]
fx3 = [f3(xi) for xi in x3]
test("Funkcja stała f(x) = 5",
	x3, fx3, f3, [1.5, 2.5, 3.5])

x4 = [1.0, 2.0, 4.0, 6.0]
fx4 = [1.0, 4.0, 8.0, 14.0]
test("Przykład z wykładu",
	x4, fx4, nothing, [])
	
println("=" ^ 50)