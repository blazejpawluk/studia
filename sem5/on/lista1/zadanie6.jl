# Błażej Pawluk

f(x) = sqrt(x * x + 1.0) - 1.0
g(x) = x * x / (sqrt(x * x + 1.0) + 1.0)

n = -1
x = 8.0^n
while x > 0 && (f(x) > 0 || g(x) > 0)
	println("x = $x, f(x) = $(f(x)), g(x) = $(g(x))")
	global n -= 1
	global x = 8.0^n
end