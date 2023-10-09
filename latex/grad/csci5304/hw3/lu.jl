using LinearAlgebra

function gauss_lu(A)
  n, _ = size(A)
  L = Matrix{Float64}(I,n,n)
  U = float.(A)

  for k=1:n-1
    for i=k+1:n
      piv = U[i,k] / U[k,k]
      for j=k:n
        U[i,j] = U[i,j] - piv * U[k,j]
      end
      L[i,k] = piv
    end
  end

  L, U
end
