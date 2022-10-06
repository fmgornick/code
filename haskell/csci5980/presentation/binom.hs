import Data.Array

tabulate :: Ix i => (i -> e) -> (i, i) -> Array i e
tabulate f bounds = array bounds [(x, f x) | x <- range bounds]

-- computes binomial coeffiecient from definition
badBinom :: Int -> Int -> Int
badBinom n r = fact n `div` (fact r * fact (n - r))
  where fact n = product [1 .. fromIntegral n]

-- ⎛n⎞ _ ⎛n-1⎞ + ⎛n-1⎞   ⎛n⎞ _ ⎛n⎞ _ 1
-- ⎝r⎠ ‾ ⎝ r ⎠ + ⎝r-1⎠,  ⎝0⎠ ‾ ⎝n⎠ ‾ 1

-- using the eualities above, we can construct a function
-- that get's binom n r from binom n-1 r and binom n-1 r-1
-- via recursion
recBinom :: Int -> Int -> Int
recBinom n r = if r == 0 || n == r 
               then 1 
               else recBinom (n - 1) r + recBinom (n - 1) (r - 1)

-- this has a lot of redundant calls though, giving the above 
-- function time complexity proportional to binom n r
-- we can use DP to keep a 2D array to store the
-- binom coeffiecients of subproblems, this way we only ever 
-- need to compute each supproblem once
dpBinom :: Int -> Int -> Int
dpBinom n r = a ! (n, r) 
  where a = tabulate f ((0, 0), (n, r))
        f (i, j) = if j == 0 || i == j 
               then 1 
               else a ! (i - 1, j) + a ! (i, j - 1)
-- this solution uses a n x r 2D array and only accesses the
-- values where i > j, which is space inefficient
