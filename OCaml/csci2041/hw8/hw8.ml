type 'a tree = Leaf | Branch of 'a tree * 'a * 'a tree

let rec find_opt : 'a . ('a -> bool) -> 'a tree -> 'a option =
  fun p t ->
    match t with
    | Leaf -> None
    | Branch (left, root, right) -> 
        match find_opt p left with
        | None -> if p root then Some root else find_opt p right
        | x -> x


exception Not_found

let rec find_exn : 'a . ('a -> bool) -> 'a tree -> 'a =
  fun p t ->
    match t with
    | Leaf -> raise Not_found
    | Branch (left, root, right) -> 
        try find_exn p left with Not_found -> if p root then root else find_exn p right

exception Assert_failure

let rec assert_all : 'a . ('a -> bool) -> 'a tree -> unit =
  fun p t ->
    match t with
    | Leaf -> ()
    | Branch (left, root, right) ->
        if p root then 
          if (assert_all p left = ()) then
            if (assert_all p right = ()) then () else raise Assert_failure
          else raise Assert_failure
        else raise Assert_failure
