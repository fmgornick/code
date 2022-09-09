data Tree a
  = Empty
  | Node a (Tree a) (Tree a)
  deriving (Eq, Show)

int_tree =
  Node
    3
    (Node 1 (Node 4 Empty Empty) Empty)
    (Node 2 Empty Empty)

str_tree =
  Node
    "I "
    (Node "really " (Node "love " Empty Empty) Empty)
    (Node "Haskell!" Empty Empty)

ints_tree :: Tree [Int]
ints_tree =
  Node
    [1, 3]
    (Node [4, 5, 6] Empty (Node [] Empty Empty))
    ( Node
        []
        (Node [1, 6] Empty Empty)
        (Node [9, 2, 8] Empty Empty)
    )

strs_tree :: Tree [String]
strs_tree =
  Node
    ["I ", "really "]
    ( Node
        ["do ", "love "]
        (Node ["Haskell! "] Empty Empty)
        (Node ["It ", "must ", "be "] Empty Empty)
    )
    ( Node
        ["your "]
        (Node ["favorite ", "too!"] Empty Empty)
        (Node [] Empty Empty)
    )

size :: Tree a -> Int
size Empty = 0
size (Node _ l r) = 1 + size l + size r

sum :: Num a => Tree a -> a
sum Empty = 0
sum (Node n l r) = n + Main.sum l + Main.sum r

product :: Num a => Tree a -> a
product Empty = 1
product (Node n l r) = n * Main.product l * Main.product r

charcount :: Tree String -> Int
charcount Empty = 0
charcount (Node str l r) = length str + charcount l + charcount r

concat :: Tree String -> String
concat Empty = ""
concat (Node str l r) = str ++ Main.concat l ++ Main.concat r

list_tree_size :: Tree [a] -> Int
list_tree_size Empty = 0
list_tree_size (Node xs l r) = length xs + list_tree_size l + list_tree_size r

list_tree_sum :: Tree [Int] -> Int
list_tree_sum Empty = 0
list_tree_sum (Node xs l r) = foldr (+) 0 xs + list_tree_sum l + list_tree_sum r

list_tree_product :: Tree [Int] -> Int
list_tree_product Empty = 1
list_tree_product (Node xs l r) = foldr (*) 1 xs * list_tree_product l * list_tree_product r

list_tree_charcount :: Tree [String] -> Int
list_tree_charcount Empty = 0
list_tree_charcount (Node xs l r) = foldr (\str acc -> acc + length str) 0 xs + list_tree_charcount l + list_tree_charcount r

list_tree_concat :: Tree [String] -> String
list_tree_concat Empty = ""
list_tree_concat (Node xs l r) = foldr (++) "" xs ++ list_tree_concat l ++ list_tree_concat r

tree_foldr :: (a -> b -> b) -> b -> Tree a -> b
tree_foldr f acc t = case t of
  Empty -> acc
  -- Node x l r -> tree_foldr f (f x (tree_foldr f acc r)) l
  Node x l r -> tree_foldr f (tree_foldr f (f x acc) r) l

tree_foldl :: (a -> b -> a) -> a -> Tree b -> a
tree_foldl f acc t = case t of
  Empty -> acc
  -- Node x l r -> tree_foldl f (f (tree_foldl f acc l) x) r
  Node x l r -> tree_foldl f (tree_foldl f (f acc x) l) r
