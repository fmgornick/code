(* typing context: empty *)
(* dynamic environment: empty *)

let x = 10
(* typing context: x : int *)
(* dynamic environment: x --> 10 *)

let y = x + 10
(* typing context: x : int, y : int *)
(* dynamic environment: x --> 10, y --> 20 *)

let x = if x = 10 then y else x
(* typing context: x : int, y : int *)
(* dynamic environment: x --> 20, y --> 20 *)

let w =
  let x = x + 10
  in
  (* typing context: w : int, x : int, y : int *)
  (* dynamic environment: w --> 600, x --> 30, y --> 20 *)
  x * y

;; (* <-- this signals the end `w`. If not for this homework assignment,
      such useless `;;` is considered a terrible coding style. *)

(* typing context: w : int, x : int, y : int *)
(* dynamic environment: w --> 600, x --> 20, y --> 20 *)
