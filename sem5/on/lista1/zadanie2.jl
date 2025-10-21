# Błażej Pawluk

println("Float16: $(Float16(3.0) * (Float16(4.0) / Float16(3.0) - Float16(1.0)) - Float16(1.0)) | $(eps(Float16))")
println("Float32: $(Float32(3.0) * (Float32(4.0) / Float32(3.0) - Float32(1.0)) - Float32(1.0)) | $(eps(Float32))")
println("Float64: $(Float64(3.0) * (Float64(4.0) / Float64(3.0) - Float64(1.0)) - Float64(1.0)) | $(eps(Float64))")