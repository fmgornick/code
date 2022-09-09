all_odds :: [Int] -> [Int]
all_odds = filter odd

decrement_all :: [Int] -> [Int]
decrement_all = map (\x -> x - 1)

min_fold :: [Int] -> Int
min_fold [] = 0
min_fold (x : xs) = foldl min x xs

sum_prod :: [Int] -> (Int, Int)
sum_prod l = (foldl (+) 0 l, foldl (*) 1 l)

partition_left :: (a -> Bool) -> [a] -> ([a], [a])
partition_left f = foldl (\(xs, ys) x -> if f x then (xs ++ [x], ys) else (xs, ys ++ [x])) ([], [])

partition_right :: (a -> Bool) -> [a] -> ([a], [a])
partition_right f = foldr (\x (xs, ys) -> if f x then (x : xs, ys) else (xs, x : ys)) ([], [])

map_as_fold :: (a -> b) -> [a] -> [b]
map_as_fold f = foldr (\x acc -> f x : acc) []
