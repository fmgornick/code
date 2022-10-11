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
-- values where i > j, which is a little space inefficient (O(nr))
-----------------------------------------------------------------
tdBinom :: Int -> Int -> Int
tdBinom n r = a ! (n, r) 
  where a = tabulate f ((0, 0), (n, r))
        f (i, j) = if j == 0 || i == j 
               then 1 
               else a ! (i - 1, j) + a ! (i - 1, j - 1)



----------------------- BETTER DP BINOM -------------------------
-- to better our space complexity, we can start with a bottom row 
-- corresponding to r = 0, this row contains r+1 1s 0C0 to rC0

-- next, we build the next row starting at 1c1 which is 1. now 
-- 2C1 = 1C1 + 1C0 which is the second element of the first row 
-- plus the first element of the current row, and the first 
-- element of the current row just starts at 1

-- since the first element of each row = 1 (kCk = 1) we can just 
-- do a scanr1 taking the first element of the list each time, 
-- we could also just do scanr with accumulator 1

-- finally, we repeat this process of adding from the previous 
-- row n-r times until we reach the last value which is nCr

-- this version uses replicate to get the first row, then scanr1 
-- does the first column of each subseqent row, meaning that the 
-- actual computation for nCr comes from the r(n - r) additions

-- also, we only have a list of length r + 1 that get's 
-- overwritten on each call, so space is O(r)
-----------------------------------------------------------------
buBinom :: Int -> Int -> Int
buBinom n r = head (apply (n - r) (scanr1 (+)) (replicate (r + 1) 1))

apply :: Int -> (a -> a) -> a -> a
apply n f x = apply (n - 1) f (f x)

