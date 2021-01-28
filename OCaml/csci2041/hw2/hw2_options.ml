(* typing context: empty *)
(* dynamic environment: empty *)

let x = Some 100

(* typing context: x : int option *)
(* dynamic environment: x --> Some 100 *)

(* The intention is to turn an option value into a list.
   More specifically, if the value is `None`, then we want an empty list.
   Otherwise, we want a singleton list holding the value tagged with `Some`.
*)
let x_as_list =
  match x with
  | None -> []
  | Some x -> 
    (* typing context: x : int *)
    (* dynamic environment: x --> 100 *)
    [x]

;; (* end of `x_as_list` *)

(* typing context: x : int option, x_as_list : int list *)
(* dynamic environment: x --> Some 100, x_as_list --> [100] *)
