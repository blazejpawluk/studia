# Błażej Pawluk
include("mbisekcji.jl")

f1(x) = 3x
f2(x) = MathConstants.e^x
delta = 10.0^-4
epsilon = 10.0^-4

f(x) = f1(x) - f2(x)

(r,fr,it,err) = mbisekcji(f, 0.0, 1.0, delta, epsilon)
println(r)
(r,fr,it,err) = mbisekcji(f, 1.0, 2.0, delta, epsilon)
println(r)