# Błażej Pawluk
include("mbisekcji.jl")
include("mstycznych.jl")
include("msiecznych.jl")

# funkcja z polecenia
f(x) = sin(x) - (0.5x)^2

# punkt 1
a = 1.5
b = 2.0
delta = 0.5 * 10^-5
epsilon = 0.5 * 10^-5
println(mbisekcji(f,a,b,delta,epsilon))

# punkt 2
pf(x) = cos(x) - 0.5x
x0 = 1.5
delta = 0.5 * 10^-5
epsilon = 0.5 * 10^-5
maxit = 10^3
println(mstycznych(f,pf,x0,delta,epsilon, maxit))

# punkt 3
x0 = 1.0
x1 = 2.0
delta = 0.5 * 10^-5
epsilon = 0.5 * 10^-5
maxit = 10^3
println(msiecznych(f,x0,x1,delta,epsilon,maxit))