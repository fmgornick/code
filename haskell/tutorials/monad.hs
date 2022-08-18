-- off brand Maybe monad
data Mayhaps a = Some a | None

return :: a -> Mayhaps a
return = Some

(>>=) :: Mayhaps a -> (a -> Mayhaps b) -> Mayhaps b
(>>=) val f = case val of
  None -> None
  Some x -> f x
