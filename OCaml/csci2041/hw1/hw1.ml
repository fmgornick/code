(* Problem 1.1: make the code compile. *)

(* Problem 1.2: fill in the typing context and dynamic environment. *)

let x = 100
(* typing context: x : int *)
(* dynamic environment: x --> 100 *)

let y = 200
(* typing context: y: int *)
(* dynamic environment: y --> 200 *)

(* The intention here is to bind z to twenty if x is greater than ten,
   or some number (any number) if x is not greater than ten. *)
let z = if x > 10 then 20 else 30
(* typing context: z: int *)
(* dynamic environment: z --> 20 *)

(* The intention here is to bind two_as_float to one plus one. *)
let two_as_float : float = 1.0 +. 1.0
(* typing context: two_as_float : float *)
(* dynamic environment: two_as_float --> 2.0 *)

(* The intention here is to bind ten to 10 if two_as_float is
   equal to 2.0 (as having the same value). *)
let ten = if two_as_float = 2.0 then 10 else 0
(* typing context: ten : int *)
(* dynamic environment: ten --> 10 *)
