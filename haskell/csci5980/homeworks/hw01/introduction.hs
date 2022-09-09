odd :: Int -> Bool
odd x = x `mod` 2 == 1

euclid :: Int -> Int -> Int
euclid x y
  | x == y = x
  | x < y = euclid x (y - x)
  | otherwise = euclid (x - y) y

frac_simplify :: (Int, Int) -> (Int, Int)
frac_simplify (x, y) = (x `div` euclid x y, y `div` euclid x y)

-- restrictions: list cannot be empty (returns 0 if empty list used)
--             : list cannot be infinite
min_list :: [Int] -> Int
min_list [] = 0
min_list [x] = x
min_list (x : xs) = min x (min_list xs)

drop :: Int -> [a] -> [a]
drop _ [] = []
drop n (x : xs)
  | n <= 0 = x : xs
  | otherwise = Main.drop (n - 1) xs
