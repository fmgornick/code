type 'a tree = Leaf | Branch of 'a tree * 'a * 'a tree

let rec find_cont : 'a 'b . ('a -> bool) -> 'a tree -> ('a -> 'b) -> (unit -> 'b) -> 'b =
  fun p t cont_found cont_notfound ->
    match t with
    | Leaf -> cont_notfound ()
    | Branch (left, root, right) ->
        let cont_notfound = fun () ->
          if p root then cont_found root else find_cont p right cont_found cont_notfound
        in find_cont p left cont_found cont_notfound
