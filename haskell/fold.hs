------------ IMPORTANT FUNCTIONS ------------
-- map :: (a -> b) -> [a] -> [b]
-- map [] = []
-- map f (x:xs) = (f x) : (map f xs)

-- foldl :: (b -> a -> b) -> b -> [a] -> b
-- foldl _ acc [] = acc
-- foldl f acc (x:xs) = foldl f (f acc x) xs

-- foldr :: (a -> b -> b) -> b -> [a] -> b
-- foldr _ acc [] = acc
-- foldr f acc (x:xs) = f x (foldr f acc xs)
---------------------------------------------

-- reverse order of list
rev :: [a] -> [a]
rev = foldl (flip (:)) [] -- appends second to first

-- get list of all lists with matching prefixes
prefixes :: [a] -> [[a]]
prefixes = foldr (\x acc -> [x] : map (x :) acc) []

lagrange :: [(Float, Float)] -> Float -> Float
lagrange xs x = foldl (\acc (x_i, y_i) -> acc + y_i * l x_i) 0 xs
  where
    l x_i =
      foldl
        ( \acc (x_j, _) ->
            if x_i == x_j
              then acc
              else acc * ((x - x_j) / (x_i - x_j))
        )
        1
        xs

data Trie a = Leaf a | Node a [Trie a]

foldtrie :: (b -> a -> b) -> b -> Trie a -> b
foldtrie f acc (Leaf x) = f acc x
foldtrie f acc (Node x xs) = foldl (foldtrie f) (f acc x) xs
