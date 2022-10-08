-- ASSIGNING TYPES TO OUR KNAPSACK
type Name      = String
type Value     = Int
type Weight    = Int
type Item      = (Name, Value, Weight)
type Selection = ([Name], Value, Weight)

-- getter functions (so we don't need to pattern match all the time)
name :: Item -> Name
name (n, _, _) = n

value :: (a, Value, Weight) -> Value
value (_, v, _) = v

weight :: (a, Value, Weight) -> Weight
weight (_, _, w) = w



----------------------------- CHOICES -----------------------------
-- first, we should write a function to return a list of selections
-- with max weight leq the specified weight capacity

-- base case: if there's no item, then our selection is nothing, so 
-- we return a selection with no names, value, or weight

-- now, if the current item has a larger weight than our max, we 
-- immediately skip to a subproblem

-- otherwise, there are two choices for our selection...
-- 1) we could still skup this item and recurse down, to gather the 
--    items we might miss if we take this one
-- 2) we could take this item and see what other grouping of 
--    selections we can make

-- for the first case, we just immediately recurse down again

-- for the second case, we want to subtract the items weight from 
-- our selection weight, get a list of all the selections of our 
-- remaining items with the modified weight, then just add our item 
-- to each of those selections

-- now to group up our selections, we conctenate the two selection 
-- lists returned by each of the subproblems, thus giving us a list 
-- of every possible selection less than the max weight
-------------------------------------------------------------------
choices :: Weight -> [Item] -> [Selection]
choices _ [] = [([], 0, 0)]
choices w (i: is) = if w < wi
                    then choices w is
                    else choices w is ++ map (add i) (choices (w - wi) is)
                    where wi = weight i

add :: Item -> Selection -> Selection
add i (ns, v, w) = (name i : ns, value i + v, weight i + w)



----------------------------- MAXWITH ------------------------------
-- this function takes in a list of elements that can't be ordered 
-- the conventional way

-- it converts each element into something with order, then compares 
-- the outputted values to extract the element with the highest value 
-- according to the function passed in

-- note: foldr1 is just a normal foldr with no accumulator, so it 
-- uses the last element of the list as the accumulator
--------------------------------------------------------------------
maxWith :: Ord b => (a -> b) -> [a] -> a
maxWith f = foldr1 (greater f)
  where greater f x y = if f x >= f y then x else y



------------------------------ SWAG -------------------------------
-- now, we call the actual swag function to make the best choice 

-- we go through all the choices, find the one with the largest 
-- value and return that selection

-- we use the maxWith function to return the actual selection with 
-- the greatest value, if instead we used a regular fold with the 
-- max function, that would only return the value of the our swag, 
-- and not the swag itself
-------------------------------------------------------------------
swag :: Weight -> [Item] -> Selection
swag w = maxWith value . choices w



-------------------------- BETTER SWAG ----------------------------
-- the first solution finds the best selection out of our possibly 
-- 2^n sized list, meaning it doesn't scale well

-- we can note that if we recurse down to a sub-selection with a 
-- modified max weight, the best selection from that is the one 
-- with the highest value

-- so instead of concatenating every possible choice of selections 
-- and finding the best choice at the end, we can just take the 
-- best selection of items if we include the current item, and 
-- compare it to the best selection of items excluding our current 
-- item and return the best of those 2

-- this optimization is only possible through the recognization of 
-- optimal substructure...

-- value s1 <= value s2 <=> value (add i s1) <= value (add i s2)
-------------------------------------------------------------------
betterSwag :: Weight -> [Item] -> Selection
betterSwag  _ [] = ([], 0, 0)
betterSwag w (i: is) = if wi > w
                       then betterSwag w is
                       else better (betterSwag w is) (add i (betterSwag (w - wi) is))
                       where wi = weight i

better :: Selection -> Selection -> Selection
better s1 s2 = maxWith value [s1, s2]



--------------------------- BEST SWAG -----------------------------
-- the previous algorithm constructs a 
-------------------------------------------------------------------
-- buSwag :: Weight -> [Item] -> Selection
-- buSwag w = head . foldr step start
--            where start = replicate (w + 1) ([], 0, 0)
--                  step i row = 

