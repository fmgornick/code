type 'a tree = Leaf | Branch of 'a tree * 'a * 'a tree

let rec count_some_tree : 'a . 'a option tree -> int =
  fun t -> 
    match t with
    | Leaf -> 0
    | Branch (left, Some _, right) -> count_some_tree left + 1 + count_some_tree right
    | Branch (left, _, right) -> count_some_tree left + 0 + count_some_tree right


let rec sum_list_tree : int list tree -> int =
  fun t -> 
    match t with
    | Leaf -> 0
    | Branch (left, root, right) -> 
        let rec sum_list : int list -> int = 
          fun l ->
            match l with
            | [] -> 0
            | h :: t -> h + sum_list t
        in sum_list_tree left + sum_list root + sum_list_tree right


let rec weighted_total_depths_helper : int tree -> int -> int =
  fun t d ->
    match t with
    | Leaf -> 0
    | Branch (left, root, right) ->
        weighted_total_depths_helper left (d+1) + d*root + weighted_total_depths_helper right (d+1)

let weighted_total_depths : int tree -> int =
  fun t -> weighted_total_depths_helper t 1


let rec expand_tree : 'a . 'a tree -> 'a tree =
  fun t -> 
    match t with
    | Leaf -> Leaf
    | Branch (left, root, right) -> 
        Branch ( Branch(expand_tree left,root,Leaf) , root , Branch(Leaf,root,expand_tree right ))
