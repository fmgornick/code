using LinearAlgebra
using DelimitedFiles

function cholR(A)
  n, _ = size(A)
  U = float.(A)
  for k = 1 : n
    U[k,k] <= 0 && error("non-positive pivot")
    U[k,k:n] = U[k,k:n] / sqrt(U[k,k])
    for i = k+1 : n
      U[i,i:n] = U[i,i:n] - U[k,i] * U[k,i:n]
    end
  end
  triu(U)
end

function cholQR(A)
  R = cholR(A'*A)
  Q = A * inv(R)
  Q, R
end

function cgsa(A)
  m,n = size(A)
  Q = Matrix{Float64}(undef,m,n)
  R = Matrix{Float64}(undef,n,n)
  for j = 1 : n
    q = A[:,j]
    a = q
    for i = 1 : j-1
      r = a' * Q[:,i]
      q = q - r * Q[:,i]
      R[i,j] = r
    end
    r = norm(q)
    r == 0 && error("zero column")
    Q[:,j] = q / r
    R[j,j] = r
  end
  Q, R
end

function mgsa(A)
  m,n = size(A)
  Q = Matrix{Float64}(undef,m,n)
  R = Matrix{Float64}(undef,n,n)
  for j = 1 : n
    q = A[:,j]
    for i = 1 : j-1
      r = q' * Q[:,i]
      q = q - r * Q[:,i]
      R[i,j] = r
    end
    r = norm(q)
    r == 0 && error("zero column")
    Q[:,j] = q / r
    R[j,j] = r
  end
  Q, R
end

function tests(file)
  res = Matrix{Float64}(undef,2,3)
  M = readdlm(file, ' ', Float64, '\n')

  Q1, R1 = cgsa(M)
  Q2, R2 = mgsa(M)
  Q3, R3 = cholQR(M)

  res[1,1] = norm(M - Q1*R1)
  res[1,2] = norm(M - Q2*R2)
  res[1,3] = norm(M - Q3*R3)

  res[2,1] = norm(I[1:5,1:5] - Q1'*Q1)
  res[2,2] = norm(I[1:5,1:5] - Q2'*Q2)
  res[2,3] = norm(I[1:5,1:5] - Q3'*Q3)

  res
end
