# Błażej Pawluk
include("mbisekcji.jl")

# funkcja znajduje i wypisuje wszystkie pierwiastki danej funkcji w przedziale
# korzysta z metody bisekcji do znajdowania pierwiastków w mniejszych przedziałach
function findRoots(f, a, b, delta, epsilon)
	interval = 2*delta
	left = a
	right = a + interval
	while right <= b
		(v,r,it,err) = mbisekcji(f,left,right,delta,epsilon)
		if err == 0
			println(v)
			left = v + interval
			right = left + interval
		else
			right += interval
		end
	end
end

f1(x) = 3x
f2(x) = MathConstants.e^x
delta = 10.0^-4
epsilon = 10.0^-4

f(x) = f1(x) - f2(x)

# można przejrzeć cały zakres funkcji w ten sposób
# findRoots(f, nextfloat(typemin(Float64)), prevfloat(typemax(Float64)), delta, epsilon)
# niebezpieczeństwa: 
# zapętlenie z powodu dodawania małych liczb do dużych, przez co wartość nie będzie zmieniana
# długi czas działania programu

# wiedząc, że e^x jest zawsze dodatnie, to sprawdzamy tylko od przedziału gdzie 3x>0
# e^x rośnie o wiele szybciej niż 3x, więc możemy już skończyć szukanie dla wartości 2
findRoots(f, 0.0, 2.0, delta, epsilon)