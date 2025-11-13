# Błażej Pawluk
include("mbisekcji.jl")
include("mstycznych.jl")
include("msiecznych.jl")

f1(x) = MathConstants.e^(1-x) - 1
pf1(x) = -MathConstants.e^(1-x)
f2(x) = x * MathConstants.e^-x
pf2(x) = (x-1) * -MathConstants.e^-x

delta = 10.0^-5
epsilon = 10.0^-5
maxit = 100

println("f1=e^(1-x)-1")
# f1 to funkcja e^x po przekształceniach: 
# 	przerzucenia w poziomie
# 	przesunięciu w prawo o 1
# 	przesunięciu w dół o 1
# zatem ma miejsce zerowe dla x=1
(r,v,it,err) = mbisekcji(f1, -1.0, 2.0, delta, epsilon)
if err == 0
	println("metoda bisekcji: $r")
end

(r,v,it,err) = mstycznych(f1, pf1, -1.0, delta, epsilon, maxit)
if err == 0
	println("metoda Newtona (x0<1): $r")
else
	println("metoda Newtona (x0<1): błąd")
end
(r,v,it,err) = mstycznych(f1, pf1, 2.0, delta, epsilon, maxit)
if err == 0
	println("metoda Newtona (x0>1): $r")
else
	println("metoda Newtona (x0>1): błąd")
end

(r,v,it,err) = msiecznych(f1, -1.0, 2.0, delta, epsilon, maxit)
if err == 0
	println("metoda siecznych: $r")
else
	println("metoda siecznych: błąd")
end

println("\nf2=xe^-x")
# f2 ma miejsce zerowe dla x=0
# ponadto dąży do 0 w nieskończoności
# ma maksimum dla x=1
(r,v,it,err) = mbisekcji(f2, -1.0, 2.0, delta, epsilon)
if err == 0
	println("metoda bisekcji: $r")
end

(r,v,it,err) = mstycznych(f2, pf2, -1.0, delta, epsilon, maxit)
if err == 0
	println("metoda Newtona (x0<1): $r")
else
	println("metoda Newtona (x0<1): błąd")
end
(r,v,it,err) = mstycznych(f2, pf2, 2.0, delta, epsilon, maxit)
if err == 0
	println("metoda Newtona (x0>1): $r")
else
	println("metoda Newtona (x0>1): błąd")
end
(r,v,it,err) = mstycznych(f2, pf2, 1.0, delta, epsilon, maxit)
if err == 0
	println("metoda Newtona (x0=1): $r")
else
	println("metoda Newtona (x0=1): błąd")
end

(r,v,it,err) = msiecznych(f2, 2.0, 3.0, delta, epsilon, maxit)
if err == 0
	println("metoda siecznych (x0,x1>1): $r")
else
	println("metoda siecznych (x0,x1>1): błąd")
end
(r,v,it,err) = msiecznych(f2, -1.0, 0.5, delta, epsilon, maxit)
if err == 0
	println("metoda siecznych (x0,x1<1): $r")
else
	println("metoda siecznych (x0,x1<1): błąd")
end