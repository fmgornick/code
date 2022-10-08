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



--------------------------- POOPY FIB ---------------------------
-- based off definition of fib function
-----------------------------------------------------------------
badFib :: Int -> Int
badFib n = if n <= 1 then 1 else badFib (n -1) + badFib (n -2)



-------------------------- TOP DOWN FIB ---------------------------
-- tabulatees an array from 0 to n where the function mapping 
-- index to element is the fib function, but the recursive call 
-- indexes the array instead of calling fib again

-- this is top down because we start by trying to solve the problem 
-- naturally, and we keep using answers from subproblems until 
-- we've recursed all the way down to the base case, finally, the 
-- aswers start to flow back up the call stack until we have our 
-- final solution
-------------------------------------------------------------------
tdFib :: Int -> Int
tdFib n = a ! n
  where a = tabulate f (0, n)
        f i = if i <= 1 
              then fromIntegral i 
              else a ! (i - 1) + a ! (i - 2)



------------------------- BOTTOM UP FIB -------------------------
-- instead of creating an n+1 length array, only tracks the two 
-- highest indexes, as that's all that's needed to calculate the 
-- next value

-- this is bottom up because it starts from the smallest 
-- subproblems and solves larger and larger subproblems based off 
-- the solution to smaller ones

-- this essentially skips the recursive sub-call like in the top 
-- down approach and moves directly to the solution.  Also has 
-- constant space complexity because we only keep track of 2 
-- values, unlike top down having a linear array
-----------------------------------------------------------------
buFib :: Int -> Int
buFib n = fst (apply n step (0, 1))
  where step (a, b) = (b, a + b)
        apply n f x = if n == 0 
                      then x 
                      else apply (n - 1) f (f x)



--------------------------- FUN FIB -----------------------------
funFib = 1 : 1 : zipWith (+) funFib (tail funFib)
-----------------------------------------------------------------

