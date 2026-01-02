function write_vector(fname::AbstractString, x::AbstractVector{Float64})
    open(fname, "w") do io
        for i in 1:length(x)
            println(io, x[i])
        end
    end
end