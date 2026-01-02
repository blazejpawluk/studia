function block_lu_solve(n::Int, l::Int, LUblocks::Vector{Matrix{Float64}},
                        pivots::Vector{Vector{Int}}, Lsub::Vector{Matrix{Float64}},
                        U_sup::Vector{Matrix{Float64}}, b::Vector{Float64})
    v = div(n,l)
    yblocks = [zeros(Float64,l) for _ in 1:v]
    bblocks = [copy(b[(k-1)*l+1 : k*l]) for k in 1:v]
    yblocks[1] .= bblocks[1]
    for k in 2:v
        yblocks[k] .= bblocks[k] - Lsub[k] * yblocks[k-1]
    end
    xblocks = [zeros(Float64,l) for _ in 1:v]
    xblocks[v] = lu_solve_small(LUblocks[v], pivots[v], reshape(yblocks[v], l, 1)) |> vec
    for k in v-1:-1:1
        rhs = yblocks[k] - U_sup[k] * xblocks[k+1]
        xblocks[k] = lu_solve_small(LUblocks[k], pivots[k], reshape(rhs, l, 1)) |> vec
    end
    return vcat(xblocks...)
end