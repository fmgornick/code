type 'a nested_list = Scalar of 'a | Nested of 'a nested_list list

let rec append : 'a . 'a list -> 'a list -> 'a list =
    fun l1 l2 ->
        match l1 with
        | [] -> l2
        | h1 :: t1 -> h1 :: append t1 l2

let rec flatten : 'a . 'a nested_list -> 'a list =
  fun l ->
      match l with
      | Scalar x -> [x]
      | Nested [] -> []
      | Nested (h::t) -> append (flatten h) (flatten (Nested t))

