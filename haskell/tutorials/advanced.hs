-- we're rewriting the insert function
import Data.List hiding (insert)
import Test.QuickCheck

-- define tree datatype
data Tree a = Leaf | Node (Tree a) a (Tree a)

-- how a tree is displayed to screen
instance (Show a) => Show (Tree a) where
  show Leaf = "leaf"
  show (Node l v r) = "node (" ++ show l ++ " " ++ show v ++ " " ++ show r ++ ")"

-- exercise 1 --
-- infTupTree: create an infinite tree of tuples
-- cut: acts like the take function but for trees

infTupTree :: Tree (Int, Int)
infTupTree = aux (0, 0)
  where
    aux (x, y) = Node (aux (x + 1, y)) (x, y) (aux (x, y + 1))

cut :: Int -> Tree a -> Tree a
cut 0 _ = Leaf
cut _ Leaf = Leaf
cut n (Node l v r) = Node (cut (n - 1) l) v (cut (n - 1) r)

-- exercise 2 --
-- insert: adds node in correct order
-- inorder: traverses tree fron left to right
-- prop: tests insert and inorder against regular sort

insert :: (Ord a) => a -> Tree a -> Tree a
insert v Leaf = Node Leaf v Leaf
insert v (Node l v' r)
  | v < v' = Node (insert v l) v' r
  | otherwise = Node l v' (insert v r)

inorder :: Tree a -> [a]
inorder Leaf = []
inorder (Node l v r) = inorder l ++ [v] ++ inorder r

-- run with quickCheck $ verbose prop
prop :: [Int] -> Property
prop xs = inorder (foldr insert Leaf xs) === sort xs
  where
    types = xs :: [Int]
