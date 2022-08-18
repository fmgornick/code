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

-- calculate lagrange of list of tuples
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

-- write a fold function for Tree
data Trie a = Leaf a | Node a [Trie a]

-- foldtriel (flip (:)) [] t prints right to left
foldtriel :: (b -> a -> b) -> b -> Trie a -> b
foldtriel f acc (Leaf x) = f acc x
foldtriel f acc (Node x xs) = foldl (foldtriel f) (f acc x) xs

-- foldtrier (:) [] t prints left to right
foldtrier :: (a -> b -> b) -> b -> Trie a -> b
foldtrier f acc val = case val of
  Leaf x -> f x acc
  Node x xs -> f x (foldr (flip $ foldtrier f) acc xs)
