# Błażej Pawluk

# macheps (otrzymany iteracyjnie wynik mnożymy *2, ponieważ otrzymana wartość nie spełnia juz warunku macheps)
macheps16 = Float16(1.0)
while Float16(1.0) + macheps16 > Float16(1.0)
	global macheps16 /= Float16(2.0)
end
println("\nmacheps(Float16) = $(Float16(2.0) * macheps16) | $(eps(Float16)) | brak")

macheps32 = Float32(1.0)
while Float32(1.0) + macheps32 > Float32(1.0)
	global macheps32 /= Float32(2.0)
end
println("macheps(Float32) = $(Float32(2.0) * macheps32) | $(eps(Float32)) | 1.1920929e7")

macheps64 = Float64(1.0)
while Float64(1.0) + macheps64 > Float64(1.0)
	global macheps64 /= Float64(2.0)
end
println("macheps(Float64) = $(Float64(2.0) * macheps64) | $(eps(Float64)) | 2.220446049250313e-16")

# liczba maszynowa eta
eta16 = Float16(1.0)
while eta16 / Float16(2.0) > Float16(0.0)
	global eta16 /= Float16(2.0)
end
println("\neta(Float16) = $eta16 | $(nextfloat(Float16(0.0)))")
println("$(bitstring(eta16))")

eta32 = Float32(1.0)
while eta32 / Float32(2.0) > Float32(0.0)
	global eta32 /= Float32(2.0)
end
println("eta(Float32) = $eta32 | $(nextfloat(Float32(0.0)))")

eta64 = Float64(1.0)
while eta64 / Float64(2.0) > Float64(0.0)
	global eta64 /= Float64(2.0)
end
println("eta(Float64) = $eta64 | $(nextfloat(Float64(0.0)))")

# floatmin
println("\nfloatmin(Float16) = $(floatmin(Float16))")
println("floatmin(Float32) = $(floatmin(Float32))")
println("floatmin(Float64) = $(floatmin(Float64))")

# max (dla otrzymanego iteracyjnie wyniku bierzemy poprzednia wartosc i mnozymy *2)
max16 = Float16(1.0)
while !isinf(Float16(2.0) * max16)
	global max16 *= Float16(2.0)
end
println("\nmax(Float16) = $(prevfloat(max16) * Float16(2.0)) | $(floatmax(Float16)) | brak")

max32 = Float32(1.0)
while !isinf(Float32(2.0) * max32)
	global max32 *= 2
end
println("max(Float32) = $(prevfloat(max32) * Float32(2.0)) | $(floatmax(Float32)) | 3.4028235e+38")

max64 = Float64(1.0)
while !isinf(Float64(2.0) * max64)
	global max64 *= 2
end
println("max(Float64) = $(prevfloat(max64) * Float64(2.0)) | $(floatmax(Float64)) | 1.7976931348623157e+308")