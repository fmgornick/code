# Fib

I saw a couple questions relating to `fib` that I'll go over, but first let's just get into the super basic `fib` function.

## Bad Fib

```haskell
badFib :: Int -> Int
badFib n = if n <= 1 then 1 else badFib (n - 2) + badFib (n - 1)
```

This is assuming the input is a natural number, I don't really feel like doing error checking.  

$O(\phi^n)$ time and space complexity, so not very good at all.

I'm sure y'all know how this works so let's just jump into the dynamic version.  And this is where the first question comes

## Tabulate Question
Q: I understand how dynamic programming works by building a table in an imperative context, but I am not sure how tabulate achieves the same effect in a functional context. Without side effects we aren't really filling in a table, so intuitively I wonder how we can be assured that the table entries are computed in the right order to be reused. Does this have something to do with lazy evaluation building a dependency digraph instead of redoing work, or is it simpler than that?

To answer this I'll quick go over how arrays work in Haskell

You can create an array with the `array` function which takes a tuple of bounds and an associative list of indexable values -> elements.

It also has it's own index operator `(!)`

**This new array data type has its own strict rules tho**

An array is undefined if any index in the list is out of bounds.  Also, if any two associations in the list have the same index, the value at that index is undefined.
 
Because the indices must be checked for errors,  `array`  is strict in the bounds argument and in the indices of the association list, but non-strict in the values.  So we CAN express an array like this:

```haskell
> fact = array (1,100) ((1,1) : [(i, i * a!(i-1)) | i <- [2..100]])
> fact!5
```

So the array is built up starting from the first index, and subsequent elements can be calculated based off the values of previous elements.  I'd imagine this is just how the `array` function is defined, but it could also have something to do with lazy evaluation, that's not really my problem tho.

Not every index needs an associated value, but if you try an access an index with no corresponding element, it will be undefined:

```haskell
> a1 = array (0,5) [(1, "fletcher"), (2, "nikunj"), (5, "ryan")]
> a1!1
> a1!2
> a1!3
```

If the lower bound is greater than the upper bound, then the array is legal, but empty.  Indexing an empty array always gives an array-bounds error, but  `bounds`  still yields the bounds with which the array was constructed:

```haskell
> a2 = array (3,1) []
> a2!0
> bounds a2
```

So our `fib` function just takes the output of `tabulate`, then returns the nth index to get our final answer, meaning our array still doesn't have state, and we're safe from being a bunch of imperative scrubs

## Fib with Tabulate

So using tabulate to write a linear time `fib` function, we get:
```haskell
tabulate :: Ix i => (i -> e) -> (i, i) -> Array i e
tabulate f bounds = array bounds [(x, f x) | x <- range bounds]

betterFib1 :: Int -> Int
betterFib1 n = a ! n
  where a = tabulate f (0, n)
        f i = if i <= 1 
              then fromIntegral i 
              else a ! (i - 1) + a ! (i - 2)
```

this version brings it down to $O(n)$ time complexity because it only calculates `fib` of each number once up until $n$, but it's also $O(n)$ space complexity because we have an $n$-length array

## Fib with tupling

We can bring space complexity down to a constant by noting that each `fib` value is only dependent on the prior two, so we can just use tuples:
```haskell
betterFib2 :: Int -> Int
betterFib2 n = fst (apply n step (0, 1))
  where step (a, b) = (b, a + b)
        apply n f x = if n == 0 
                      then x 
                      else apply (n - 1) f (f x)
```

## Logarithmic Fib
Another question I got was to go over the two `fib` functions given in the exercises

The first one was actually covered by Eric in a previous lecture, but I'll quickly go over it

```haskell
funFib = 1 : 1 : zipWith (+) funFib (tail funFib)
```
