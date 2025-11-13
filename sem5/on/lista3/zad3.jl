# Błażej Pawluk
include("msiecznych.jl")

f(x) = x^2 + 2x - 3
delta = 10.0^-3
epsilon = 10.0^-3
maxit = 10^3

# sprawdzanie różnych punktów początkowych
xs = [
	(2.0, 3.0),
	(2.0, 1.0),
	(0.0, 2.0),
	(0.0, 3.0),
	(-1.0, 2.0),
	(-3.0, 2.0),
	(3.0, -4.0),
	(-4.0, 2.0),
	(-2.0, 0.0)
]
for (x0,x1) in xs
	println("x0=$x0, x1=$x1: $(msiecznych(f,x0,x1,delta,epsilon,maxit))")
end