# Błażej Pawluk

# punkt 1
# stałe początkowe
p0 = 0.01
r = 3

# liczniki na sposob 1 i 2
pn1 = p0
pn2 = p0

println("Punkt 1 (sposób 1 - bez zaokraglania | sposób 2 - z zaokraglaniem w p_10)")
println("p0 = $pn1 | $pn2")

for i in 1:40
	global pn1 = pn1 + r*pn1*(1.0-pn1)

	global pn2 = pn2 + r*pn2*(1.0-pn2)
	if i == 10
		global pn2 = round(pn2; digits=3)
	end

	println("p$i = $pn1 | $pn2")
end

# punkt 2
# stałe poczatkowe takie jak w punkcie 1

# liczniki
pn32 = Float32(p0)
pn64 = Float64(p0)

println("\nPunkt 2 (Float32 | Float64)")
println("p0 = $pn32 | $pn64")

for i in 1:40
	global pn32 = pn32 + r*pn32*(Float32(1.0)-pn32)
	global pn64 = pn64 + r*pn64*(Float64(1.0)-pn64)

	println("p$i = $pn32 | $pn64")
end

# generowanie pliku z danymi do wykresu
pn1 = p0
pn2 = p0
pn32 = Float32(p0)
pn64 = Float64(p0)

filename = "data/wyniki5.txt"
open(filename, "w") do io
	write(io, "0 $pn1 $pn2 $pn32 $pn64\n")
	for i in 1:40
		global pn1 = pn1 + r*pn1*(1.0-pn1)
		
		global pn2 = pn2 + r*pn2*(1.0-pn2)
		if i == 10
			global pn2 = round(pn2; digits=3)
		end
		
		global pn32 = pn32 + r*pn32*(Float32(1.0)-pn32)
		
		global pn64 = pn64 + r*pn64*(Float64(1.0)-pn64)
		
		write(io, "$i $pn1 $pn2 $pn32 $pn64\n")
	end
end
println("Zapisano dane w pliku $filename.")