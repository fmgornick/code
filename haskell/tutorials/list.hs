-- check if an item is an element of a list
element :: (Eq a) => a -> [a] -> Bool
element _ [] = False
element t (x : xs) = t == x || element t xs

-- removes duplicates of a list
nub :: (Eq a) => [a] -> [a]
nub [] = []
nub (x : xs)
  | x `elem` xs = nub xs
  | otherwise = x : nub xs

-- check if a list is in descending order
isAsc :: (Ord a) => [a] -> Bool
isAsc [] = True
isAsc [_] = True
isAsc (x : y : xs) = y >= x && isAsc (y : xs)

-- check if there exists a path from one value to another
-- given a list of tuples
hasPath :: (Eq a) => [(a, a)] -> a -> a -> Bool
hasPath [] x y = x == y
hasPath paths x y
  | x == y = True
  | otherwise =
    let newpaths = [(m, n) | (m, n) <- paths, m /= x]
     in or [hasPath newpaths n y | (m, n) <- paths, m == x]
