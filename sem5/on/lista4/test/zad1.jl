# Błażej Pawluk, 279738

include("../src/ilorazyRoznicowe.jl")
using .IlorazyRoznicowe

function test(nazwa, x, f, expected)
	println("TEST: ", nazwa)
	println("x = ", x)
	println("f = ", f)

	println("\nOczekiwane:")
	for i in eachindex(expected)
		println("\t$(i-1) = $(expected[i])")
	end

	fx = ilorazyRoznicowe(x, f)
	println("\nOtrzymane:")
	for i in eachindex(fx)
		println("  [$(i-1)] = $(fx[i])")
	end

	println("\nRóżnice:")
	maxDiff = 0.0
	for i in eachindex(expected)
		diff = abs(fx[i] - expected[i])
		maxDiff = max(maxDiff, diff)
		println("\t[$(i-1)] różnica = $diff")
	end
	println("Maksymalna różnica: $maxDiff")
	println()
end

println("=" ^ 50)
println("TESTY ILORAZYROZNICOWE")
println("=" ^ 50)
println()

test("Prosty przykład", 
	[1.0, 2.0, 4.0], 
	[1.0, 4.0, 8.0],
	[1.0, 3.0, -1.0/3.0])

test("Funkcja liniowa f(x) = 2x + 3",
	[0.0, 1.0, 2.0, 3.0],
	[3.0, 5.0, 7.0, 9.0],
	[3.0, 2.0, 0.0, 0.0])

test("Funkcja kwadratowa f(x) = x^2",
	[0.0, 1.0, 2.0, 3.0],
	[0.0, 1.0, 4.0, 9.0],
	[0.0, 1.0, 1.0, 0.0])

test("Funkcja stała f(x) = 5",
	[1.0, 2.0, 3.0, 4.0],
	[5.0, 5.0, 5.0, 5.0],
	[5.0, 0.0, 0.0, 0.0])

test("Przykład z wykładu",
	[1.0, 2.0, 4.0, 6.0],
	[1.0, 4.0, 8.0, 14.0],
	[1.0, 3.0, -1.0/3.0, 7.0/60.0])

println("=" ^ 50)