let two = 2
(* typing context: two : int *)
(* dynamic environment: two --> 2 *)

(* The intention was to bind z to 10 if `two' is not zero
   and 20 if `two' is zero. Try to minimize the changes! *)
(* WRONG: if two <> 0 then let z = 10 else let z = 20 *)
let z = if two <> 0 then 10 else 20
(* typing context: z : int *)
(* dynamic environment: z --> 10 *)
