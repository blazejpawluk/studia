# funkcja wczytuje dane z podanego pliku i parsuje je na input problemu LP

function parseInput(filename)
	lines = readlines(filename)

	mode = lowercase(lines[1])

	n = parse(Int, lines[2])

	costs = [parse(Float64, t) for t in split(lines[3])]

	A = Float64[]
	b = Float64[]
	for i in 4:length(lines)
		line = split(lines[i])
		Ai = [parse(Float64, v) for v in line[1:n]]
		append!(A, Ai)
		push!(b, parse(Float64, line[n+1]))
	end
	A = reshape(A, n, length(b))'

	return mode, n, costs, A, b
end