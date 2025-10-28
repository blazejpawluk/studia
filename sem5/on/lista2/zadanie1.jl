# Błażej Pawluk

x32 = Float32[2.718281828, -3.141592654, 1.414213562, 0.577215664, 0.301029995]
y32 = Float32[1486.2497, 878366.9879, -22.37492, 4773714.647, 0.000185049]

x64 = Float64[2.718281828, -3.141592654, 1.414213562, 0.577215664, 0.301029995]
y64 = Float64[1486.2497, 878366.9879, -22.37492, 4773714.647, 0.000185049]

# dokładna wartość iloczynu skalarnego wektorów x i y
real = Float64(-1.00657107000000 * 10^-11)

# sposob 1 - w przód
S32 = Float32(0.0)
S64 = Float64(0.0)
for i in 1:5
	global S32 += x32[i] * y32[i]
	global S64 += x64[i] * y64[i]
end

println("Sposób 1:")
println("$S32 | $S64 | $real")

# sposob 2 - w tył
S32 = Float32(0.0)
S64 = Float64(0.0)
for i in 5:-1:1
	global S32 += x32[i] * y32[i]
	global S64 += x64[i] * y64[i]
end

println("Sposób 2:")
println("$S32 | $S64 | $real")

# liczenie sum częsciowym i dzielenie ich na podtablice z wartościami ujemnymi i dodatnimi, aby je posortować do sposobów 3 i 4
partS32N = Float32[]
partS32P = Float32[]
partS64N = Float64[]
partS64P = Float64[]
for i in 1:5
	xi32 = x32[i] * y32[i]
	if xi32 < 0
		push!(partS32N, xi32)
	else
		push!(partS32P, xi32)
	end
	
	xi64 = x64[i] * y64[i]
	if xi32 < 0
		push!(partS64N, xi64)
	else
		push!(partS64P, xi64)
	end
end

# sposob 3 - od największego
sort(partS32N)
sort(partS32P, rev=true)
sort(partS64N)
sort(partS64P, rev=true)

# sumy podtablic
S32N = Float32(0.0)
S32P = Float32(0.0)
S64N = Float64(0.0)
S64P = Float64(0.0)

for x in partS32N
	global S32N += x
end
for x in partS32P
	global S32P += x
end
for x in partS64N
	global S64N += x
end
for x in partS64P
	global S64P += x
end

S32 = S32N + S32P
S64 = S64N + S64P

println("Sposób 3:")
println("$S32 | $S64 | $real")

# sposob 4 - od najmniejszych
sort(partS32N, rev=true)
sort(partS32P)
sort(partS64N, rev=true)
sort(partS64P)

S32N = Float32(0.0)
S32P = Float32(0.0)
S64N = Float64(0.0)
S64P = Float64(0.0)

for x in partS32N
	global S32N += x
end
for x in partS32P
	global S32P += x
end
for x in partS64N
	global S64N += x
end
for x in partS64P
	global S64P += x
end

S32 = S32N + S32P
S64 = S64N + S64P

println("Sposób 4:")
println("$S32 | $S64 | $real")