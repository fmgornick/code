(* typing context: empty *)
(* dynamic environment: empty *)

let x = (1, true)

(* typing context: x : int * bool *)
(* dynamic environment: x --> (1, true) *)

(* The intention is to swap the two components of x. *)
let swapped_x =
  match x with
  | (x, y) ->
    (* typing context: <FILL IN YOUR ANSWER> *)
    (* dynamic environment: <FILL IN YOUR ANSWER> *)
    (y, x)

;; (* end of `x_as_list` *)

(* typing context: <FILL IN YOUR ANSWER> *)
(* dynamic environment: <FILL IN YOUR ANSWER> *)
