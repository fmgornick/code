(* typing context: empty *)
(* dynamic environment: empty *)

let x = (1, true)

(* typing context: x : int * bool *)
(* dynamic environment: x --> (1, true) *)

(* The intention is to swap the two components of x. *)
let swapped_x =
  match x with
  | (x, y) ->
    (* typing context: x : int, y : bool *)
    (* dynamic environment: x --> 1, y --> true *)
    (y, x)

;; (* end of `x_as_list` *)

(* typing context: x : int * bool, swapped_x : bool * int *)
(* dynamic environment: x --> (1, true), swapped_x --> (true, 1) *)
