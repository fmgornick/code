type 'a nested_list = Scalar of 'a | Nested of 'a nested_list list

let flatten : 'a . 'a nested_list -> 'a list =
  fun l ->
    if l = Scalar _ then [l]
    else fh l

let rec fh : 'a . 'a nested_list -> 'a list =
  fun l ->
    match l with
    | Scalar x -> x
