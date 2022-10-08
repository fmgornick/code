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



----------------------------- MAXWITH ------------------------------
-- this function takes in a list of elements that can't be ordered 
-- the conventional way

-- it converts each element into something with order, then compares 
-- the outputted values to extract the element with the lowest value 
-- according to the function passed in

-- note: foldr1 is just a normal foldr with no accumulator, so it 
-- uses the last element of the list as the accumulator
--------------------------------------------------------------------
minWith :: Ord b => (a -> b) -> [a] -> a
minWith f = foldr1 (less f)
  where less f x y = if f x <= f y then x else y

mce :: [Char] -> [Char] -> [Op]
mce xs ys = minWith cost (edits xs ys)
