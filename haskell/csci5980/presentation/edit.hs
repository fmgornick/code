----------------------------- OP TYPE ------------------------------
-- this type consists of 4 operations you can do on a string to 
-- output a new string

-- Copy:    0 time units
-- Replace: 3 time units
-- Insert:  2 time units
-- Delete:  2 time units

-- Replace is more efficient than an Insert + Delete, otherwise 
-- there'd be no reason for Replace
--------------------------------------------------------------------
data Op = Copy Char | Replace Char Char | Insert Char | Delete Char



--------------------------- RECONSTRUCT ----------------------------
-- takes a list of operations and constructs a tuple with thee first 
-- string being the "before" and the second string being "after"

-- we MUST use foldr in this case because the last operation 
-- corresponds to the last thing we do to our string, so it should 
-- be the first thing we do when reconstructing our string from 
-- nothing
--------------------------------------------------------------------
reconstruct :: [Op] -> ([Char], [Char])
reconstruct = foldr step ([], [])
  where step (Copy x)      (us, vs) = (x : us, x : vs)
        step (Replace x y) (us, vs) = (x : us, y : vs)
        step (Insert x)    (us, vs) = (us, x : vs)
        step (Delete x)    (us, vs) = (x : us, vs)



------------------------------ COST --------------------------------
-- computes the operverall cost for a sequence of operations

-- book does sum . map ecost which iterates through list twice, so 
-- i change to foldr
--------------------------------------------------------------------
cost :: [Op] -> Int
cost = foldr (\op base -> base + ecost op) 0 
  where ecost (Copy _)      = 0
        ecost (Replace _ _) = 3
        ecost (Insert _)    = 2
        ecost (Delete _)    = 2



--------------------------- POOPY EDITS ----------------------------
-- first, we define minWith, which is just the opposite of maxWith 
-- from the knapsack problem

-- the edits function is what does most of the work here.  It takes 
-- the two strings and produces a list of lists containing every 
-- possible sequence of operations to go from the first string to 

-- for each point, edits splits into 3 potential operation sequences 
-- for the strings xs and ys:
-- 1) Copy / Replace: detailed by the pick function recurses down to 
--    the xs-1 and ys-1 case
-- 2) Insert: adds value to ys then recurses to xs, ys-1 case
-- 3) Insert: remove value from xs then recurses to xs-1, ys case

-- once it gets all the lists for the possible sub-edits, it 
-- concatenates them all together

-- finally mce is function that uses minWith to find the specific 
-- sequence of operations with the least cost to return
--------------------------------------------------------------------
minWith :: Ord b => (a -> b) -> [a] -> a
minWith f = foldr1 (less f)
  where less f x y = if f x <= f y then x else y


edits :: [Char] -> [Char] -> [[Op]]
edits xs []             = [map Delete xs]
edits [] ys             = [map Insert ys]
edits (x : xs) (y : ys) = [pick x y : es | es <- edits xs ys      ] ++
                          [Insert y : es | es <- edits (x : xs) ys] ++
                          [Delete x : es | es <- edits xs (y : ys)]

pick :: Char -> Char -> Op
pick x y = if x == y then Copy x else Replace x y

mce :: [Char] -> [Char] -> [Op]
mce xs ys = minWith cost (edits xs ys)



--------------------------- BETTER EDITS ---------------------------
-- we can speed this up significantly with dynamic programming by 
-- noting the following inequality showing optimal substructure

-- cost es1 <= cost es2 <=> cost (op : es1) <= cost (op : es2)

-- so instead of taking the entire list of suboperations for each 
-- possible operation, we can instead just take the best one from 
-- each of the sub-edits, and return the best of the 3

-- the Copy operation takes 0 time, so we can optimize this even 
-- more by just doing a copy whenever the case comes up.  I won't 
-- prove why copy is a greedy choice tho cuz this is the DP chapter
--------------------------------------------------------------------
mceBetter :: [Char] -> [Char] -> [Op]
mceBetter xs []             = map Delete xs
mceBetter [] ys             = map Insert ys
mceBetter (x : xs) (y : ys) = minWith cost [
                                pick x y : mceBetter xs ys,
                                Insert y : mceBetter (x : xs) ys,
                                Delete x : mceBetter xs (y : ys)
                              ]

mcBest :: [Char] -> [Char] -> [Op]
mcBest xs ys = head (foldr (nextrow xs) (firstrow xs) ys)

firstrow = tail . map Delete

nextrow :: [Char] -> Char -> [[Op]] -> [[Op]]
nextrow xs y row = foldr step [Insert y : last row] xes
  where xes = zip3 xs row (tail row)
        step (x, es1, es2) row = if x == y
                                 then (Copy x : es2) : row
                                 else minWith cost [Replace x y : es2,
                                        Delete x : head row,
                                        Insert y : es1] : row



