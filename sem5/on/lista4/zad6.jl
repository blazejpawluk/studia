# Błażej Pawluk, 279738

include("src/rysujNnfx.jl")
using .RysujNnfx
using Plots

println("a) f(x) = |x|")
fa(x) = abs(x)
a = -1.0
b = 1.0
ns = [5,10,15]
for n in ns
	println("\tn=$n")
	savefig(rysujNnfx(fa, a, b, n), "output/zad6/fa-$n-r.png")
	savefig(rysujNnfx(fa, a, b, n, wezly=:czebyszew), "output/zad6/fa-$n-c.png")
end

println("\nb) f(x) = 1/(1+x^2)")
fb(x) = 1 / (1 + x^2)
a = -5.0
b = 5.0
ns = [5,10,15]
for n in ns
	println("\tn=$n")
	savefig(rysujNnfx(fb, a, b, n), "output/zad6/fb-$n-r.png")
	savefig(rysujNnfx(fb, a, b, n, wezly=:czebyszew), "output/zad6/fb-$n-c.png")
end