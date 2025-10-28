# Błażej Pawluk

# funkcja do wykonywania iteracji dla stałych
function iterate(x0, c, point)
	println("\nPunkt $point")
	
	# licznik
	xn = x0
	println("x0 = $xn")

	for i in 1:40
		xn = xn^2 + c
		println("x$i = $xn")
	end
end

# punkt 1
iterate(1.0, -2.0, 1)

# punkt 2
iterate(2.0, -2.0, 2)

# punkt 3
iterate(1.99999999999999, -2.0, 3)

# punkt 4
iterate(1.0, -1.0, 4)

# punkt 5
iterate(-1.0, -1.0, 5)

# punkt 6
iterate(0.75, -1.0, 6)

# punkt 7
iterate(0.25, -1.0, 7) 