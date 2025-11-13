# Błażej Pawluk
include("mstycznych.jl")

f(x) = (x/2)^2 + sin(x)
pf(x) = x/2 + cos(x)
delta = 10.0^-20
epsilon = 10.0^-20
maxit = 10^3

println("Zmiana początkowego przybliżenia:")
xs = [-100.0, -2.0, -1.9337537628462, -1.5, -1.0298665299928, 0.0, 2.0, 3.5]
for x0 in xs
	println("x0=$x0: $(mstycznych(f, pf, x0, delta, epsilon, maxit))")
end

println("\noczekiwany błąd przekroczenia max iteracji:")
maxit = 10
x0 = -1.0298665299928
println("$(mstycznych(f, pf, x0, delta, epsilon, maxit))")

println("\noczekiwany błąd pochodnej bliskiej 0:")
f(x) = x^2 + 2x - 3
pf(x) = 2x + 2
x0 = -1.0
println("$(mstycznych(f, pf, x0, delta, epsilon, maxit))")