# z biblioteki
# funkcje na stronie Zieliński PWR
# Dawid ma ładnie rozpisane

# Błażej Pawluk
using LinearAlgebra

function hilb(n::Int)
# Function generates the Hilbert matrix  A of size n,
#  A (i, j) = 1 / (i + j - 1)
# Inputs:
#	n: size of matrix A, n>=1
#
#
# Usage: hilb(10)
#
# Pawel Zielinski
	if n < 1
		error("size n should be >= 1")
	end
	return [1 / (i + j - 1) for i in 1:n, j in 1:n]
end

function matcond(n::Int, c::Float64)
# Function generates a random square matrix A of size n with
# a given condition number c.
# Inputs:
#	n: size of matrix A, n>1
#	c: condition of matrix A, c>= 1.0
#
# Usage: matcond(10, 100.0)
#
# Pawel Zielinski
        if n < 2
         error("size n should be > 1")
        end
        if c< 1.0
         error("condition number  c of a matrix  should be >= 1.0")
        end
        (U,S,V)=svd(rand(n,n))
        return U*diagm(0 =>[LinRange(1.0,c,n);])*V'
end

# wylicza wartość b
function calculateB(A, n) 
	x = ones(n,1)
	return A*x
end

# wylicza błąd bezwzględny
function relativeError(x, realX)
	dNorm = norm(x - realX)
	rNorm = norm(realX)

	if rNorm == 0
		return dNorm == 0 ? 0.0 : Inf
	end
	return dNorm / rNorm
end


# macierz Hilberta
println("Macierz Hilberta:")

for n in 5:25
	A = hilb(n)
	b = calculateB(A, n)
	
	# dokładna wartość x=(1, .., 1)^T
	realX = ones(n,1)
	
	x1 = A\b
	x2 = inv(A)*b
	println("$n: $(relativeError(x1, realX)) | $(relativeError(x2, realX))")
end

# losowa macierz
println("\nLosowa macierz:")

cs = [0,1,3,7,12,16]
ns = [5,10,20]
for c in cs
	for n in ns
		A = matcond(n, 10.0^c)
		b = calculateB(A, n)
		
		# dokładna wartość x=(1, .., 1)^T
		realX = ones(n,1)

		x1 = A\b
		x2 = inv(A)*b
		println("$n 10^$c: $(relativeError(x1, realX)) | $(relativeError(x2, realX))")
	end
end

# generowanie danych do wykresu
filename = "data/wyniki3.txt"
open(filename, "w") do io
	for n in 5:25
		A = hilb(n)
		b = calculateB(A, n)
		realX = ones(n,1)
		
		x1 = A\b
		x2 = inv(A)*b
		write(io, "0 $n $(relativeError(x1, realX)) $(relativeError(x2, realX)) 0\n")
	end

	cs = [0,1,3,7,12,16]
	ns = [5,10,20]
	for c in cs
		for n in ns
			A = matcond(n, 10.0^c)
			b = calculateB(A, n)
			realX = ones(n,1)

			x1 = A\b
			x2 = inv(A)*b
			write(io, "1 $n $(relativeError(x1, realX)) $(relativeError(x2, realX)) $c\n")
		end
	end
end
println("\nZapisano dane w pliku $filename.")