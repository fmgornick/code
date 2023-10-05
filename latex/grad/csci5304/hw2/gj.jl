using LinearAlgebra

function gauss_jordan(A)
  A = float.(A)
  n, _ = size(A)
  M = Matrix{Float64}(I,n,n)
  d = [0.0 for i=1:n]

  for k=1:n
    for i=1:n
      i==k && continue
      piv = A[i,k] / A[k,k]
      for j=k+1:n
        A[i,j] = A[i,j] - piv * A[k,j]
      end
      M[i,k] = piv
      d[k] = A[k,k]
    end
  end

  M, d
end


function linear_systems(A, B)
  B = B[:,:]
  M, d = gauss_jordan(A)
  n, p = size(B)
  X = zeros(n,p)

  for pp=1:p 
    b = float.(B[:,pp])
    for k=1:n 
      for i=1:n 
        i==k && continue
        b[i] = b[i] + M[i,k] * b[k]
      end
    end

    for j=1:n
      X[j,pp] = b[j] / d[j]
    end
  end

  X
end
