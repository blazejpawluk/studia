# Błażej Pawluk, 279738

include("../src/rysujNnfx.jl")
using .RysujNnfx
using Plots

println("=" ^ 50)
println("TESTY RYSUJNNFX")
println("=" ^ 50)
println()

a = 0.0
b = 10.0
n = 5

f1(x) = 2x + 3
println("Funkcja: 2x+3")
println("\trównoodległe")
savefig(rysujNnfx(f1, a, b, n), "output/test4/f1-r.png")
println("\tczebyszew")
savefig(rysujNnfx(f1, a, b, n, wezly=:czebyszew), "output/test4/f1-c.png")

f2(x) = x^2
println("\nFunkcja: x^2")
println("\trównoodległe")
savefig(rysujNnfx(f2, a, b, n), "output/test4/f2-r.png")
println("\tczebyszew")
savefig(rysujNnfx(f2, a, b, n, wezly=:czebyszew), "output/test4/f2-c.png")

f3(x) = 5.0
println("\nFunkcja: 5")
println("\trównoodległe")
savefig(rysujNnfx(f3, a, b, n), "output/test4/f3-r.png")
println("\tczebyszew")
savefig(rysujNnfx(f3, a, b, n, wezly=:czebyszew), "output/test4/f3-c.png")

f4(x) = exp(2*x) + cos(1 + x)
println("\nFunkcja: e^(2x) + cos(1+x)")
println("\trównoodległe")
savefig(rysujNnfx(f4, a, b, n), "output/test4/f4-r.png")
println("\tczebyszew")
savefig(rysujNnfx(f4, a, b, n, wezly=:czebyszew), "output/test4/f4-c.png")
	
println("=" ^ 50)