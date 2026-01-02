function read_vector(fname::AbstractString)
	v = Float64[]
	open(fname, "r") do io
		lines = readlines(io)
		lines = filter(x -> strip(x) != "" && !startswith(strip(x), "#"), lines)
		if length(lines) < 1
			error("Empty b file")
		end
		n = parse(Int, split(strip(lines[1]))[1])
		if length(lines) < n+1
			error("b file has fewer lines than expected")
		end
		for i in 1:n
			push!(v, parse(Float64, strip(lines[i+1])))
		end
	end
	return v
end