----------------------------- ARRAY -----------------------------
-- Array i e: this is an array with indicies 'i' and elements 'e'

-- Ix: type class that restricts what can be an index 
-- (usually int or char)

-- array :: Ix i => (i, i) -> [(i, e)] -> Array i e
-- takes bounds and a list of associated (index, value) pairs and
-- constructs an array out of it
-----------------------------------------------------------------
import Data.Array



--------------------------- TABULATE ----------------------------
-- input: function that maps an index value into an array element
--      : index boundaries for array
-- output: array of values mapped from their indexes
-----------------------------------------------------------------
tabulate :: Ix i => (i -> e) -> (i, i) -> Array i e
tabulate f bounds = array bounds [(x, f x) | x <- range bounds]



------------------------- POOPY BINOM ---------------------------
-- computes binomial coeffiecient from definition

-- ⎛n⎞ _ ____n!____
-- ⎝r⎠ ‾ r!(n - r)!
-----------------------------------------------------------------
badBinom :: Int -> Int -> Int
badBinom n r = fact n `div` (fact r * fact (n - r))
  where fact n = product [1 .. fromIntegral n]



----------------------- RECURSIVE BINOM -------------------------
-- computes binomial coeffiecients using the below equalities for 
-- the base case and recursive step

-- ⎛n⎞ _ ⎛n-1⎞ + ⎛n-1⎞   ⎛n⎞ _ ⎛n⎞ _ 1
-- ⎝r⎠ ‾ ⎝ r ⎠ + ⎝r-1⎠,  ⎝0⎠ ‾ ⎝n⎠ ‾ 1

-- similar to fib, this recursive definition has a lot of 
-- repeating subproblems.  n choose r to computations to be 
-- exact
-----------------------------------------------------------------
recBinom :: Int -> Int -> Int
recBinom n r = if r == 0 || n == r 
               then 1 
               else recBinom (n - 1) r + recBinom (n - 1) (r - 1)



-------------------------- DP BINOM -----------------------------
-- we can use DP to keep a 2D array to store the
-- binom coeffiecients of subproblems, this way we only ever 
-- need to compute each supproblem once

-- this solution uses a n x r 2D array and only accesses the
-- values where i > j, which is a little space inefficient
-----------------------------------------------------------------
dpBinom :: Int -> Int -> Int
dpBinom n r = a ! (n, r) 
  where a = tabulate f ((0, 0), (n, r))
        f (i, j) = if j == 0 || i == j 
               then 1 
               else a ! (i - 1, j) + a ! (i, j - 1)

