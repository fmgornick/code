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
    (* typing context: x : int list, h : int, t : int list*)
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
  (* <FILL IN YOUR ANSWER>

     Don't forget the requested typing context and dynamic environment
     within the pattern matching.
   *)

;; (* this is the end of `tail_of_x` *)

(* Use only `::`, `100`, and `x` to complete the following binding.
   The intention is to prepend the integer `100` to the list `x`. *)
let x_prepended_with_one_hundred : int list =
  (* <FILL IN YOUR ANSWER> *)
