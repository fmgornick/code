-- 2.1 basic evaluator
data Term = Con Int
          | Div Term Term
          | Add Term Term
  deriving (Eq, Show)

eval0 :: Term -> Int
eval0 (Con a) = a
eval0 (Div t u) = eval0 t `div` eval u
eval0 (Add t u) = eval0 t + eval u



-- 2.2 exceptions
data Mexp a = Raise Exception
            | Return a
  deriving (Eq, Show)
type Exception = String

eval2 :: Term -> Mexcp Int
eval2 (Con a) = Return a
eval2 (Add t u) = case eval2 t of
                    Raise e -> Raise e
                    Return a -> case eval2 u of
                      Raise e -> Raise e
                      Return b -> if b == 0
                                  then Raise "bad"
                                  else Return (a `div` b)
eval2 (Add t u) = case eval2 t of
                    Raise e -> Raise e
                    Return a -> case eval2 u of
                      Raise e -> Raise e
                      Return b -> Return (a + b)


-- 2.3 state
type Mstate a = State -> (a, State)
type State = Int

eval3 :: Term -> Mstate Int
eval3 (Con a) x = (a, x)
eval3 (Div t u) x =
  let (a, y) = eval3 t x in
  let (b, z) = eval3 u y in 
  (a `div` b, z + 1)
eval3 (Add t u) x =
  let (a, y) = eval3 t x in
  let (b, z) = eval3 u y in 
  (a + b, z + 1)



-- 2.4 output
type Mout a = (Output, a)
type Output = String

eval4 :: Term -> Mout Int
eval4 (Con a) = (line (Con a), a, a)
eval4 (Div t u) =
  let (x, a) = eval4 t in
  let (y, b) = eval4 u in
  (x ++ y ++ line (Add t u) (a + b), a + b)

line :: Term -> Int -> Output
line t a = "eval (" ++ show t ++ ") <= " ++ show a ++ "\n"


class Monad m where
  (>>=)  :: m a -> (a -> m b) -> m b -- bind operator
  (>>)   :: m a -> m b        -> m b -- sequence operator
  return :: a                 -> m a

evalM :: (Monad m) => Term -> m Int
evalM (Con a) = return a
evalM (Div t u) = evalM t >>= (\a -> 
                  evalM u >>= \b -> return (a `div` b))
evalM (Add t u) = evalM t >>= (\a -> 
                  evalM u >>= \b -> return (a + b))


instance Functor Mexcp where
  fmap _ (Raise e)  = Raise e
  fmap f (Return x) = Return (f x)

instance Applicative Mexcp where
  pure = Return
  Retrun f <*> m = fmap f m
  Raise e <*> m = Raise e

instance Monad Mexcp where
  return x = Return x
  me >>= f = case me of
               Return a -> f a
               Raise e  -> Raise e


eval2m :: Term -> Mexcp Int
eval2m (Con a) = return a
eval2m (Div t u) = eval2m t >>= (\a -> 
                   eval2m u >>= \b -> if b == 0 
                                      then Raise "error: divide by zero" 
                                      else Return (a `div` b))
eval2m (Add t u) = eval2m t >>= (\a -> 
                   eval2m u >>= \b -> return (a + b))

eval2mdo :: Term -> Mexcp Int
eval2mdo (Con a) = return a
eval2mdo (Div t u) = 
  do a <- eval2mdo t
     b <- eval2mdo u
     if b == 0
     then raise "error: divide by zero"
     else Return (a `div` b))
eval2mdo (Add t u) = 
  do a <- eval2mdo t
     b <- eval2mdo u
     Return (a + b))


evalMaybe :: Term -> Maybe Int
evalMaybe (Con a) = return a
evalMaybe(Div t u) = do tv <- evalMaybe t
                        uv <- evalMaybe u
                        if uv == 0 
                        then Nothing
                        else Just (tv `div` uv)
evalMaybe(Add t u) = do tv <- evalMaybe t
                        uv <- evalMaybe u
                        Just (tv + uv)

evalIO :: Term -> IO Int
evalIO (Con a) = do putStr (line (Con a) a)
                    return a
evalIO (Div t u) =
  do a <- evalIO t
     b <- evalIO u
     putStr (line (Add t u) (a + b))
     return (a + b)
evalIO (Div t u) =
  do a <- evalIO t
     b <- evalIO u
     if b == 0
     then putStrLn "shiiiiii" >> return 0
     else do putStr (line (Div t u) (a `div` b))
             return (a + b)





