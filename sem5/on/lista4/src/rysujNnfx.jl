module RysujNnfx

export rysujNnfx

include("../src/IlorazyRoznicowe.jl")
include("../src/WarNewton.jl")

using Plots
using .IlorazyRoznicowe
using .WarNewton

function rysujNnfx(f, a::Float64, b::Float64, n::Int; wezly::Symbol = :rownoodlegle)
	# tworzenie węzłów
	xNodes = Vector{Float64}(undef, n+1)
	if wezly == :rownoodlegle
		h = (b-a) / n
		xNodes = [a + k*h for k in 0:n]
	elseif wezly == :czebyszew
		xNodes = [(a+b)/2 + (b-a)/2 * cos((2k+1)*pi / (2*(n+1))) for k in 0:n]
	end

	# wartości w wyliczonych węzłach
	yNodes = f.(xNodes)

	# współczynniki Newtona
	c = ilorazyRoznicowe(xNodes, yNodes)

	# stworzenie siatki do wykresu
	plotX = range(a, b, length=100)
	plotF = f.(plotX)

	# wyliczenie wartości wielomianu w punktach
	plotNn = [warNewton(xNodes, c, t) for t in plotX]

	# tworzenie wykresu
	p = plot(plotX, plotF, label="f(x)", title="Interpolacja stopnia n=$n") # oryginalna funkcja
	plot!(p, plotX, plotNn, label="N_n(x)", linestyle=:dash) # wielomian interpolacyjny
	scatter!(p, xNodes, yNodes, label="węzły") # dodatkowe zaznaczenie węzłów interpolacji

	display(p)
	return p
end

end