module blocksys

using LinearAlgebra

export read_block_matrix, read_vector, write_vector, matvec_block, gaussian_block_solve, block_lu_factor, block_lu_solve

include("block_lu_factor.jl")
include("block_lu_solve.jl")
include("gaussian_block_solve.jl")
include("lu_factor_small.jl")
include("lu_solve_small.jl")
include("matvec_block.jl")
include("read_block_matrix.jl")
include("read_vector.jl")
include("write_vector.jl")

end # module