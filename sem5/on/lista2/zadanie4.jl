# Błażej Pawluk

using Polynomials

# parametry wielomianu z pliku
param = [1, -210.0, 20615.0, -1256850.0,
		53327946.0, -1672280820.0, 40171771630.0, -756111184500.0,          
		11310276995381.0, -135585182899530.0,
		1307535010540395.0, -10142299865511450.0,
		63030812099294896.0, -311333643161390640.0,
		1206647803780373360.0, -3599979517947607200.0,
		8037811822645051776.0, -12870931245150988800.0,
		13803759753640704000.0, -8752948036761600000.0,
		2432902008176640000.0]
param = reverse(param)

# funkcja P (zgodna z definicją w treści zadania)
function P(x)
	result = 0.0
	for n in 1:21
		result += param[n]*x^(n-1)
	end
	return result
end

# funkcja p (zgodna z definicją z treści zadania)
function p(x)
	result = 1.0
	for n in 1:20
		result *= (x-n)
	end
	return result
end

# punkt a
println("a)")
z = roots(Polynomial(param))
println("Pierwiastki z funkcji roots: $z")

println("\nSprawdzenie pierwiastków:")
for k in 1:20
	Px = abs(P(z[k])) # |P(zk)|
	px = abs(p(z[k])) # |p(zk)|
	diff = abs(z[k]-k) # |zk-k|

	println("$k: |P(zk)|=$Px, |p(xk)|=$px, |zk-k|=$diff")
end

# punkt b
println("\nb)")
param[20] -= 2^-23
z = roots(Polynomial(param))
println("Pierwiastki z funkcji roots: $z")

println("\nSprawdzenie pierwiastków:")
for k in 1:20
	Px = abs(P(z[k])) # |P(zk)|
	px = abs(p(z[k])) # |p(zk)|
	diff = abs(z[k]-k) # |zk-k|

	println("$k: |P(zk)|=$Px, |p(xk)|=$px, |zk-k|=$diff")
end