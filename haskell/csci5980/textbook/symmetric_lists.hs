type SymList a = ([a], [a])

toSL :: [a] -> SymList a
toSL [] = ([], [])
toSL xs = (us, reverse vs) where (us, vs) = splitAt (length xs `div` 2) xs

fromSL :: SymList a -> [a]
fromSL (xs, ys) = xs ++ reverse ys

consSL :: a -> SymList a -> SymList a
consSL x (xs, ys) = if null ys then ([x], xs) else (x : xs, ys)

snocSL :: a -> SymList a -> SymList a
snocSL y (xs, ys) = if null xs then (ys, [y]) else (xs, y : ys)

single :: [a] -> Bool
single [] = False
single (x : xs) = null xs

tailSL :: SymList a -> SymList a
tailSL (xs, ys)
  | null xs = if null ys then error "penis" else ([], [])
  | single xs = (reverse vs, us)
  | otherwise = (tail xs, ys)
  where
    (us, vs) = splitAt (length ys `div` 2) ys

initSL :: SymList a -> SymList a
initSL (xs, ys)
  | null ys = if null xs then error "sinep" else ([], [])
  | single ys = (us, reverse vs)
  | otherwise = (xs, tail ys)
  where
    (us, vs) = splitAt (length xs `div` 2) xs
