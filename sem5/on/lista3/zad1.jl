# Błażej Pawluk
include("mbisekcji.jl")

# miejsca zerowe funckji: -3, 1
f(x) = x^2 + 2x - 3
x1 = -3.0
x2 = 1.0

# miejsce zerowe na granicy
print("oczekiwane $x1: ")
println(mbisekcji(f, x1, -2.0, 10.0^-3, 10.0^-3))
print("\noczekiwane $x2: ")
println(mbisekcji(f, 0.0, x2, 10.0^-3, 10.0^-3))

# funkcja nie zmienia znaku
print("\noczekiwany błąd: ")
println(mbisekcji(f, x2+1.0, x2+2.0, 10.0^-3, 10.0^-3))

# miejsce zerowe na środku przedziału
print("\noczekiwane $x2: ")
println(mbisekcji(f, x1-1.0, x1+1.0, 10.0^-3, 10.0^-3))

# miejsce zerowe w innym miejscu z różną dokłądnością
a = x2-1.0
b = x2+2.0
println("\nróżne dokładności, oczekiwane $x2:")
for i in 1:20
	dokladnosc = 10.0^-i
	print("dokładność=$dokladnosc: ")
	println(mbisekcji(f, a, b, dokladnosc, dokladnosc))
end