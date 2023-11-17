using LinearAlgebra
using DelimitedFiles

function house(X)
  X = deepcopy(X)
  m,n = size(X); V = zeros(m,n); bet = zeros(n)

  for k = 1 : n
    S = X[k:m,k:n]
    v,b = house1(S[:,1])

    X[k:m,k:n] = S - b * v * v' * S
    V[k:m,k] = v; bet[k] = b
  end

  V, bet
end

function house1(x) 
  m = size(x)[1]
  m == 1 && return 1, 0

  v = [1 ; x[2:m]]
  sigma = v[2:m]' * v[2:m]

  if (sigma == 0) 
    bet = 0
  else
    xnrm = sqrt(x[1]^2 + sigma)
    v[1] = (x[1] <= 0 ? x[1] - xnrm : x[1] + xnrm)

    bet = 2 / (1+sigma/v[1]^2)
    v = v / v[1]
  end

  v, bet
end

function house_qr(X)
  V, bet = house(X)
  m = size(V)[1]; n = size(bet)[1]
  eye = Float64.(I[1:m,1:m])
  Q = eye; R =  deepcopy(X)

  for j = 1 : n
    k = n + 1 - j

    Rp = R[j:m,j:n]; v = V[j:m,j]; b = bet[j]
    R[j:m,j:n] = Rp - b * v * v' * Rp
    R[j+1:m,j] = zeros(m-j)

    v = V[:,k]; b = bet[k]
    Q = Q - b * v * v' * Q
  end
  Q, R
end

function get_data()
  res = Matrix{Float64}(undef,2,3)
  M = readdlm("p5_data.txt", ' ', Float64, '\n')
  M
end
