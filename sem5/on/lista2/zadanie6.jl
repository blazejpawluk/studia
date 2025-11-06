# Błażej Pawluk
using Plots

iterations = 40
f(x,c) = x^2 + c

# funkcja do wykonywania iteracji dla stałych
function iterate(x0, c, point)
	
	# przeprowadzenie iteracji
	x = [0.0 for i in 1:iterations+1]
	x[1] = x0
	for i in 1:iterations
		x[i+1] = f(x[i], c)
	end
	
	# wypisanie wyników
	println("\nPunkt $point")
	for i in 1:length(x)
		println("x_{$(i-1)} = $(x[i])")
	end

	# tworzenie wykresu
	minx = minimum(x)
	maxx = maximum(x)
	xplot = range(minx-1, maxx+1, length=400)
	yplot = [f(x,c) for x in xplot]

	# rysowanie f(x), y=x
	plt = plot(xplot, yplot, label="f(x)=x^2+$c", legend=:topright)
	plot!(xplot, xplot, label="y=x")

	# tworzenie iteracji graficznej
	xi = Float64[]
	yi = Float64[]
	for i in 1:iterations
		push!(xi, x[i])
		push!(yi, x[i])
		push!(xi, x[i])
		push!(yi, x[i+1])
		push!(xi, x[i+1])
		push!(yi, x[i+1])
	end

	# rysowanie iteracji graficznej
	plot!(xi, yi, label="iteracja graficzna", color=:green)
	scatter!(x, x, label="x_n", color=:green, markerstrokecolor=:green)

	# zapisanie wykresu
	title!("$point.Wykres iteracji graficznej: f(x)=x^2+$(c), x_0=$(x0), c=$c", titlefontsize=8)
	xlabel!("x")
	ylabel!("f(x)")

	filename = "charts/zadanie6-$point.png"
	savefig(plt, filename)
	println("Iterację graficzną zapisano w pliku $filename.")
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