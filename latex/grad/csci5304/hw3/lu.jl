using LinearAlgebra                      |      julia> L,U = gauss_lu(A)
                                         |      
function gauss_lu(A)                     |      julia> L
  n, _ = size(A)                         |      3×3 Matrix{Float64}:
  L = Matrix{Float64}(I,n,n)             |        1.0   0.0        0.0
  U = float.(A)                          |       -2.0   1.0        0.0
                                         |       -1.0  -0.0909091  1.0
  for k=1:n-1                            |      
    for i=k+1:n                          |      julia> U
      piv = U[i,k] / U[k,k]              |      3×3 Matrix{Float64}:
      for j=k:n                          |       2.0   3.0  -1.0
        U[i,j] = U[i,j] - piv * U[k,j]   |       0.0  11.0  -2.0
      end                                |       0.0   0.0   4.81818
      L[i,k] = piv                       |    
    end                                  |       julia> L * U
  end                                    |       3×3 Matrix{Float64}:
                                         |         2.0   3.0  -1.0
  L, U                                   |        -4.0   5.0   0.0
end                                      |        -2.0  -4.0   6.0
