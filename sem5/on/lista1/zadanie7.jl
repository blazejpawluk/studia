# Błażej Pawluk

f(x) = sin(x) + 3cos(x)

x0 = 1.0
real = -1.98411064855554
for n in 0:54
	h = 2.0^-n
	fd = (f(x0 + h) - f(x0)) / h
	println("h = $h, f'(x0) = $fd, blad = $(abs(real - fd))")
end