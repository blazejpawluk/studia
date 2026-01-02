function lu_solve_small(LU::Matrix{Float64}, piv::Vector{Int}, B::AbstractArray{Float64})
    n = size(LU,1)
    if size(B,1) != n
        error("Dimension mismatch in lu_solve_small")
    end
    Pb = copy(B[piv, :])
    m = size(Pb,2)
    Y = zeros(n, m)
    for i in 1:n
        row = copy(Pb[i,:])
        for j in 1:i-1
            row .-= LU[i,j] * Y[j,:]
        end
        Y[i,:] .= row
    end
    X = zeros(n, m)
    for i in n:-1:1
        row = copy(Y[i,:])
        for j in i+1:n
            row .-= LU[i,j] * X[j,:]
        end
        X[i,:] .= row / LU[i,i]
    end
    return m==1 ? vec(X) : X
end