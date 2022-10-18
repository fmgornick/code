---
geometry: margin=2cm
---

# Fib

Okay let's just jump right into the functional programming approach to fib.  This is how you would define it based off the recursive definition alone

```haskell
fib :: Int -> Int
fib n = if n <= 1 then 1 else fib (n - 2) + fib (n - 1)
```

$O(\phi^n)$ not good blah blah blah you get it, before showing how to optimize this with DP , I saw this piazza question so I'll go over Haskell arrays and tabulate a bit first.

## Tabulate Question
Q: I understand how dynamic programming works by building a table in an imperative context, but I am not sure how tabulate achieves the same effect in a functional context. Without side effects we aren't really filling in a table, so intuitively I wonder how we can be assured that the table entries are computed in the right order to be reused. Does this have something to do with lazy evaluation building a dependency digraph instead of redoing work, or is it simpler than that?

So digraph is a silly word that I don't really know, but if by that you mean we can construct index values based on the result of previous index values, then yes, that's pretty much how we use arrays in Haskell.  We can map indexes to values with no dependencies but I'm sure if that's all you wanna do, then you prolly don't need an array to do it.

But basically tabulate is called just once and generates the entire array in one go, so there's no state that gets maintained or anything, so we're still purely functional.  Lets quick cover how arrays work before we use them in our functions

You can create an array with the `array` function which takes a tuple of bounds and an associative list of indexable values -> elements.

It also has it's own index operator `(!)`

**This new array data type has its own strict rules tho**

An array is undefined if any index in the list is out of bounds.  Also, if 2 distinct elements have the same index, it becomes undefined
 
Because the indices must be checked for errors,  `array`  is strict in the bounds argument and in the indices of the association list, but non-strict in the values.  So we CAN use lazy evaluation to calculate the values of an array like so

```haskell
> a1 = array (0,100) ((0,1) : (1,1) : [(i, a1!(i-1) + a1!(i-2)) | i <- range (2, 100)])
> a1!5
```

Also I saw a piazza post to go over some fib function textbook exercises, so I'll quick mention the one line fib that Eric did near the start of the semester, but I don't know if there'll be enough time to go over the logarithmic `fib`
```
fib = 1 : 1 : zipWith (+) fib (tail fib)
```

Couple other rules about arrays: not every index needs an associated value, but if you try an access an index with no corresponding element, it will be undefined:

```haskell
> a2 = array (0,5) [(1, "fletcher"), (2, "nikunj"), (5, "ryan")]
> a2!1
> a2!2
> a2!3
```

If the lower bound is greater than the upper bound, then the array is legal, but empty.  Indexing an empty array always gives an array-bounds error, but  `bounds`  still yields the bounds with which the array was constructed:

```haskell
> a3 = array (3,1) []
> a3!0
> bounds a3
```

So when we call `fib` with `tabulate`, it doesn't maintain state through calls, it just generates the entire array at once and we just pick out the desired index

```haskell
tabulate :: Ix i => (i -> e) -> (i, i) -> Array i e
tabulate f bounds = array bounds [(idx, f idx) | idx <- range bounds]
```

For time sake I'll just show the tabulate version of `fib` as well as the tupling optimization, because I'll basically be doing the same thing for `binom`

## Fib with Tabulate

```haskell
fib' :: Int -> Int
fib' n = a ! n
  where a = tabulate f (0, n)
        f i = if i <= 1 
              then fromIntegral i 
              else a ! (i - 1) + a ! (i - 2)
```

## Fib with tupling

Using tupling, we can free up even more space
```haskell
fib'' :: Int -> Int
fib'' n = fst (apply n step (0, 1))
  where step (a, b) = (b, a + b)
        apply n f x = if n == 0 
                      then x 
                      else apply (n - 1) f (f x)
```

## Logarithmic Fib
Another question I got was to go over the two `fib` function exercises, I'll cover the easy one now and do the $O(\lg n)$ example later if there's still time.  If not I have an explanation at the end of the slides

This one was actually covered by Eric, but it's pretty cool so I wanna do it

```haskell
funFib = 1 : 1 : zipWith (+) funFib (tail funFib)
```

# Binom
I'm sure most of us know what the formula for the binomial coefficients are, some of you know it as choose: $\begin{pmatrix}n\\ r\end{pmatrix} = \displaystyle\frac{n!}{r!(n-1)!}$.  We can define `binom` in terms of this definition like so:

## Conventional Definition
```haskell
binom :: Int -> Int -> Int
binom n r = fact n `div` fact r * fact (n - r)
  where fact x = product [1 .. fromIntegral x]
```

We can also define `binom` recursively:
$\begin{pmatrix}n\\ r\end{pmatrix} = \begin{pmatrix}n - 1\\ r\end{pmatrix} + \begin{pmatrix}n - 1\\ r - 1\end{pmatrix}$.  The recursive definition of `binom` looks like this:

## Recursive Definition
```haskell
binom' :: Int -> Int -> Int
binom' n r = if n == r || r == 0
             then 1
             else binom' (n - 1) r + binom' (n - 1) (r - 1)
```

As it turns out, tuples are considered indexable values, so we can use our recursive definition for `binom` in our tabulate function like so:

## Binom with Tabulate
```haskell
tabulate :: Ix i => (i -> e) -> (i, i) -> Array i e
tabulate f bounds = array bounds [(i, f i) | i <- range bounds]

binom''' :: Int -> Int -> Int
binom''' n r = a ! (n, r)
  where a = tabulate f ((0, 0), (n, r))
  f (n', r') = if n' == r' || r' == 0
               then 1
               else a!(n' - 1, r') + a!(n' - 1, r' - 1)
```

So it tabulates in order of indices outputted from the Data.Array.range function.  This approach uses $r(n-r)$ additions and no multiplications with an $r \times n-r$ array.

```haskell
> import Data.Array
> range ((0, 0), (6, 3))
```

We can optimize our space by introducing a new algorithm that only needs list of length $n+1$.

This algorithm is a little wacky so I'll show you a couple tools we'll be using

## Space Efficient Binom
```haskell
-- applies function against accumulator on each element of list (starting from right)
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr _ base [] = base
foldr f base (x:xs) = f x (foldr f base xs)

-- same as foldr, but adds each intermediate result into resultant list
scanr :: (a -> b -> b) -> b -> [a] -> [b]
scanr _ base [] = [base]
scanr f base (x:xs) = f x (head xs') : xs'
  where xs' = scanr f base xs

-- same thing but starting value is the new accumulator
scanr1 :: (a -> a -> a) -> [a] -> [a]
scanr1 _ [x] = [x]
scanr1 f (x:xs) = f x (head xs') : xs'
  where xs' = scanr1 f xs

-- creates list of repeating numbers
replicate :: Int -> a -> [a]
replicate n x = if n == 0 then [] else x : replicate (n-1) x
```

For an example, let's try to calculate $\begin{pmatrix}6 \\ 3\end{pmatrix}\;\;$.

We can use the recursive definition to create a directed graph of sub-problems

First, note that a $\rightarrow$ corresponds to $\begin{pmatrix}i \\ j\end{pmatrix} \rightarrow \begin{pmatrix}i-1 \\ j-1\end{pmatrix}$ and a $\downarrow$ corresponds to $\begin{pmatrix}i \\ j\end{pmatrix} \downarrow \begin{pmatrix}i-1 \\ j\end{pmatrix}$

$\begin{pmatrix} \begin{pmatrix}6 \\ 3\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}5 \\ 2\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}4 \\ 1\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}3 \\ 0\end{pmatrix} \\ 
\downarrow &&
\downarrow &&
\downarrow &&
\downarrow \\
\begin{pmatrix}5 \\ 3\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}4 \\ 2\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}3 \\ 1\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}2 \\ 0\end{pmatrix} \\ 
\downarrow &&
\downarrow &&
\downarrow &&
\downarrow \\
\begin{pmatrix}4 \\ 3\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}3 \\ 2\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}2 \\ 1\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}1 \\ 0\end{pmatrix} \\ 
\downarrow &&
\downarrow &&
\downarrow &&
\downarrow \\
\begin{pmatrix}3 \\ 3\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}2 \\ 2\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}1 \\ 1\end{pmatrix} & 
\rightarrow & 
\begin{pmatrix}0 \\ 0\end{pmatrix}
\end{pmatrix}\;\; \Rightarrow \;\; \begin{pmatrix} 20 & 10 & 4 & 1 \\ 10 & 6 & 3 & 1 \\ 4 & 3 & 2 & 1 \\ 1 & 1 & 1 & 1\end{pmatrix}$.

This matrix has $n-r+1$ rows and $r+1$.  The last row and the last column always only contain ones, so we can construct our solution starting from the bottom row.  To start, we initialize a list of $r+1$ ones with `replicate (r + 1) 1`

Each row depends directly on the row below it, as well as the each cell to the right, but the rightmost cell is a base case, so we know that each row depends only on a row below.  So we know we can construct an algorithm that's $O(r)$ space.

We can use `scanr` to add each cell below with an accumulator starting at $0$, but this would generate a list with the $0$ as the last element, so we would need to call `init` as well which is slow, so we can instead use `scanr1` which just uses the last element in the list as the accumulator, which we want to be $1$ anyway

`init . scanr (+) 0 (replicate (r + 1) 1)` $\Rightarrow$ `scanr1 (+) (replicate (r + 1) 1)`

Now that we have a function that maps one row to the next, we just need to call this a total of $n-r$ times to get to the top row, this is where `apply` comes in

```haskell
apply :: Int -> (a -> a) -> a -> a
apply n f x = if n <= 0 then x else apply (n - 1) f (f x)
```

So we just call `apply` with the above `scan` on our replicated list of ones, and we have the top row.  Finally, we can just call `head` to get the index we want:

```haskell
binom''' :: Int -> Int -> Int
binom''' n r = head (apply (n - r) (scanr1 (+)) (replicate (r + 1) 1))
```

## Efficiency Question
Someone also asked if we could instead tabulate using the normal definition with factorial.  So we would store an $n-length$ array of factorials for reference.  That would look something like this I think:

```haskell
binom'''' :: Int -> Int -> Int
binom'''' n r = a!n `div` a!r * a!(n-r)
  where a = tabulate f (0,n)
        f i = if i == 0 then 1 else i * a!(i-1)
```

So our recursive DP `binom` takes $r(n-r)$ additions, whereas this one based off factorial takes like $n$ multiplications plus a multiplication and a division, and since their both considered constant time operations, I think on paper this is faster, but if I were a computer I would rather do the additions.

Also I don't think this solution actually changes the time complexity from the one from the original definition anyway because all we're really doing is is saving a little extra time to calculate $r!$ and $(n-r)!$
