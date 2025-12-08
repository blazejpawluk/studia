# Błażej Pawluk, 279738

include("src/rysujNnfx.jl")
using .RysujNnfx
using Plots

println("a) f(x) = e^x")
fa(x) = exp(x)
a = 0.0
b = 1.0
ns = [5,10,15]
for n in ns
	println("\tn=$n")
	savefig(rysujNnfx(fa, a, b, n), "output/zad5/fa-$n.png")
end

println("\nb) f(x) = x^2 * sin(x)")
fb(x) = x^2 * sin(x)
a = -1.0
b = 1.0
ns = [5,10,15]
for n in ns
	println("\tn=$n")
	savefig(rysujNnfx(fb, a, b, n), "output/zad5/fb-$n.png")
end