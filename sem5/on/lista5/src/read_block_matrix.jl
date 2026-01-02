function read_block_matrix(fname::AbstractString)
	open(fname, "r") do io
		lines = readlines(io)

		lines = filter(x -> strip(x) != "" && !startswith(strip(x),"#"), lines)
		if length(lines) == 0
			error("Empty file")
		end

		firsttok = split(strip(lines[1]))
		n = parse(Int, firsttok[1])
		l = parse(Int, firsttok[2])
		@assert n % l == 0 "n must be divisible by l"
		v = Int(div(n, l))

		diag = [zeros(Float64, l, l) for k in 1:v]
		sub = [zeros(Float64, l, l) for k in 1:v]
		sup = [zeros(Float64, l, l) for k in 1:v]

		for line in lines[2:end]
			parts = split(strip(line))
			if length(parts) < 3
				continue
			end
			i = parse(Int, parts[1])
			j = parse(Int, parts[2])
			val = parse(Float64, parts[3])

			bi = Int(div((i-1), l)) + 1
			bj = Int(div((j-1), l)) + 1
			li = (i-1) % l + 1
			lj = (j-1) % l + 1
			if bi == bj
				diag[bi][li, lj] = val
			elseif bi == bj + 1
				sub[bi][li, lj] = val
			elseif bi + 1 == bj
				sup[bi][li, lj] = val
			else
				error("Non-block-tridiagonal element detected at ($i,$j)")
			end
		end
		return (n, l, diag, sub, sup)
	end
end