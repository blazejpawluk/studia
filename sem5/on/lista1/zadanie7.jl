# Błażej Pawluk

f(x) = sin(x) + 3cos(x)

# dokładna wartość pochodnej
real = -1.98411064855554

x0 = 1.0
for n in 0:54
	h = 2.0^-n
	fd = (f(x0 + h) - f(x0)) / h

	# ładne wypisywanie 
	# println("h = $h, f'(x0) = $fd, blad = $(abs(real - fd))")

	# wypisywanie do wykresów
	println("$n $h $fd $real $(abs(real - fd))")
end