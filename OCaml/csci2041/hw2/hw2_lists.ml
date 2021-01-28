(* typing context: empty *)
(* dynamic environment: empty *)

let x = [1; 2; 3]
(* typing context: x : int list *)
(* dynamic environment: x --> [1; 2; 3] *)

(* the intention is to compute the head of `x` *)
let head_of_x : int option =
  match x with
  | [] -> None
  | h :: t ->
    (* typing context: x : int list, h : int, t : int list *)
    (* dynamic environment: x --> [1; 2; 3], h --> 1, t --> [2; 3] *)
    Some h

;; (* this is the end of `head_of_x` *)

(* The intention is to compute the tail of `x`.

   You should mimic the style of `head_of_x` above. That is, you should
   explain the typing context and dynamic environment at the start of
   the non-empty branch. If you think you can copy-and-paste something
   and change only one character, think again. It is not that trivial.
*)
let tail_of_x : int list option =
  match x with
  | [] -> None
  | h :: t -> 
    (* typing context: x : int list, head_of_x : int option, h : int, t : int list *)
    (* dynamic environment: x --> [1; 2; 3], head_of_x --> Some 1, h --> 1, t --> [2; 3] *)
    match t with
    | [] -> None
    | h :: t -> 
      (* typing context: x : int list, head_of_x : int option, h : int, t : int list *)
      (* dynamic environment: x --> [1; 2; 3], head_of_x --> Some 1, h --> 2, t --> [3] *)
      Some (h :: t)
      

;; (* this is the end of `tail_of_x` *)

(* Use only `::`, `100`, and `x` to complete the following binding.
   The intention is to prepend the integer `100` to the list `x`. *)
let x_prepended_with_one_hundred : int list = 100 :: x
(* typing context: x : int list, head_of_x : int option, tail_of_x : int list option, 
   x_prepended_with_one_hundred : int list *)
(* dynamic environment: x --> [1; 2; 3], head_of_x --> Some 1, tail_of_x --> Some [2; 3], 
   x_prepended_with_one_hundred --> [100; 1; 2; 3] *)
