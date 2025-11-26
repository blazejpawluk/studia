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
r1,fr1,it1,err1 = mbisekcji(f,a,b,delta,epsilon)

# punkt 2
pf(x) = cos(x) - 0.5x
x0 = 1.5
delta = 0.5 * 10^-5
epsilon = 0.5 * 10^-5
maxit = 10^3
r2,fr2,it2,err2 = mstycznych(f,pf,x0,delta,epsilon, maxit)

# punkt 3
x0 = 1.0
x1 = 2.0
delta = 0.5 * 10^-5
epsilon = 0.5 * 10^-5
maxit = 10^3
r3,fr3,it3,err3 = msiecznych(f,x0,x1,delta,epsilon,maxit)

# wypisywanie wyników w formacie tabeli do sprawozdania
println("        metoda &\$r\$ &\$f(r)\$ &\$it\$ &\$err\$ \\\\ \\hline")
println("        bisekcji &$r1 &$fr1 &$it1 &$err1 \\\\")
println("        Newtona &$r2 &$fr2 &$it2 &$err2 \\\\")
println("        siecznych &$r3 &$fr3 &$it3 &$err3 \\\\")