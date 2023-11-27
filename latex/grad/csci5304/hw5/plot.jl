using LinearAlgebra
using Plots

function plot()
  A = [4.0 8.0 4.0; 
       9.0 3.0 8.0; 
       2.0 6.0 1.0; 
       7.0 4.0 4.0; 
       8.0 3.0 6.0; 
       3.0 8.0 0.0]

  x = [i * 0.5 for i=0:20]
  y = [0.0 for i=0:20]

  for i = 1 : 21
    A[6,3] = x[i]
    S,V,D = svd(A)
    y[i] = V[3]
  end

  plot!(x, y, seriestype=:scatter, label="\$\\delta\$")
  title!("SVD Solution")
  xlabel!("Smallest Singular Value")
  ylabel!("Ann's Rating of Title 6")
end
