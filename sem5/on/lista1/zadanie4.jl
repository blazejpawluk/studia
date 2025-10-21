# Błażej Pawluk

x = nextfloat(Float64(1.0))
while x * (Float64(1.0) / x) == Float64(1.0)
	global x = nextfloat(x)
end

println("x = $x")
println("x*(1/x) = $(x * (Float64(1.0) / x))")