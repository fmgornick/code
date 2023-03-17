import time
t = (time.time() - 6 * 3600) // 1
nt = t % 86400

h = nt // 3600
h1 = h // 10
h2 = h % 10

m = (nt - (h * 3600)) // 60
m1 = m // 10
m2 = m % 10

print(int(h1),int(h2) , ":" , int(m1),int(m2))
