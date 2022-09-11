data Tree a
  = Empty
  | Node a (Tree a) (Tree a)
  deriving (Eq, Show)

------------------------ SAMPLE INPUT ------------------------
--------------------------------------------------------------
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

--------------------------------------------------------------
--------------------------------------------------------------

--------------------------- PART 3 ---------------------------
--------------------------------------------------------------
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

--------------------------------------------------------------
--------------------------------------------------------------

--------------------------- PART 4 ---------------------------
--------------------------------------------------------------
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

--------------------------------------------------------------
--------------------------------------------------------------

--------------------------- PART 5 ---------------------------
--------------------------------------------------------------
fold_tree :: (a -> b -> b) -> b -> Tree a -> b
fold_tree _ acc Empty = acc
fold_tree f acc (Node x l r) = fold_tree f (fold_tree f (f x acc) l) r

size_r :: Tree a -> Int
size_r = fold_tree (\_ acc -> acc + 1) 0

sum_r :: Num a => Tree a -> a
sum_r = fold_tree (flip (+)) 0

product_r :: Num a => Tree a -> a
product_r = fold_tree (flip (*)) 1

charcount_r :: Tree String -> Int
charcount_r = fold_tree (\str acc -> acc + length str) 0

concat_r :: Tree String -> String
concat_r = fold_tree (flip (++)) ""

list_tree_size_r :: Tree [a] -> Int
list_tree_size_r = fold_tree (\list acc -> acc + foldr (\_ acc -> acc + 1) 0 list) 0

list_tree_sum_r :: Tree [Int] -> Int
list_tree_sum_r = fold_tree (\list acc -> acc + foldr (\x acc -> acc + x) 0 list) 0

list_tree_product_r :: Tree [Int] -> Int
list_tree_product_r = fold_tree (\list acc -> acc * foldr (\x acc -> acc * x) 1 list) 1

list_tree_charcount_r :: Tree [String] -> Int
list_tree_charcount_r = fold_tree (\list acc -> acc + foldr (\str acc -> acc + length str) 0 list) 0

list_tree_concat_r :: Tree [String] -> String
list_tree_concat_r = fold_tree (\list acc -> acc ++ foldr (++) "" list) ""

--------------------------------------------------------------
--------------------------------------------------------------
