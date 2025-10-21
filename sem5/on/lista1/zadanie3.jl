# Błażej Pawluk

# [1,2]
println("1 + 2^-53 = $(Float64(1.0) + Float64(2^-53))")
println("$(bitstring(Float64(1.0) + Float64(2^-53)))")

println("\n1 + 2^-52 = $(Float64(1.0) + Float64(2^-52))")
println("$(bitstring(Float64(1.0) + Float64(2^-52)))")

println("\n1.5 + 2^-53 = $(Float64(1.5) + Float64(2^-53))")
println("$(bitstring(Float64(1.5) + Float64(2^-53)))")

println("\n1.5 + 2^-52 = $(Float64(1.5) + Float64(2^-52))")
println("$(bitstring(Float64(1.5) + Float64(2^-52)))")

# [0.5, 1]
println("\n================================================================")

println("\n0.5 + 2^-54 = $(Float64(0.5) + Float64(2^-54))")
println("$(bitstring(Float64(0.5) + Float64(2^-54)))")

println("\n0.5 + 2^-53 = $(Float64(0.5) + Float64(2^-53))")
println("$(bitstring(Float64(0.5) + Float64(2^-53)))")

println("\n0.75 + 2^-54 = $(Float64(0.75) + Float64(2^-54))")
println("$(bitstring(Float64(0.75) + Float64(2^-54)))")

println("\n0.75 + 2^-53 = $(Float64(0.75) + Float64(2^-53))")
println("$(bitstring(Float64(0.75) + Float64(2^-53)))")

# [2,4]
println("\n================================================================")

println("\n2 + 2^-52 = $(Float64(2.0) + Float64(2^-52))")
println("$(bitstring(Float64(2.0) + Float64(2^-52)))")

println("\n2 + 2^-51 = $(Float64(2.0) + Float64(2^-51))")
println("$(bitstring(Float64(2.0) + Float64(2^-51)))")

println("\n3 + 2^-52 = $(Float64(3.0) + Float64(2^-52))")
println("$(bitstring(Float64(3.0) + Float64(2^-52)))")

println("\n3 + 2^-51 = $(Float64(3.0) + Float64(2^-51))")
println("$(bitstring(Float64(3.0) + Float64(2^-51)))")