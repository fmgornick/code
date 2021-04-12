(* STOP! You should not change this file. *)

module type STACK =
sig
  type 'a t
  val empty : 'a t
  val is_empty : 'a t -> bool
  val push : 'a -> 'a t -> 'a t
  val pop : 'a t -> ('a * 'a t) option
end

module Stack : STACK =
struct
  type 'a t = 'a list
  let empty = []
  let is_empty l = match l with [] -> true | _ -> false
  let push x l = x :: l
  let pop l = match l with [] -> None | h :: t -> Some (h, t)
end
