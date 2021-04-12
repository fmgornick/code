open Hw9_stack (* this brings in the stack implementation *)

module type QUEUE_AS_TWO_STACKS =
sig
  type 'a t = 'a Stack.t * 'a Stack.t
  val empty : 'a t
  val is_empty : 'a t -> bool
  val enqueue : 'a -> 'a t -> 'a t
  val dequeue : 'a t -> ('a * 'a t) option
end

module Queue : QUEUE_AS_TWO_STACKS =
struct
  type 'a t = 'a Stack.t * 'a Stack.t
  let empty : 'a . 'a t = (Stack.empty, Stack.empty)
  let is_empty : 'a . 'a t -> bool = fun q ->
    match q with (s1, s2) ->
      if Stack.is_empty s1 then if Stack.is_empty s2 then true else false else false

  let rec append_rev : 'a . 'a Stack.t -> 'a Stack.t -> 'a Stack.t = fun s1 s2 ->
    match (Stack.pop s2) with 
    | None -> s1
    | Some (value, new_s2) -> append_rev (Stack.push value s1) new_s2

  let enqueue : 'a . 'a -> 'a t -> 'a t = fun x q ->
    match q with (s1, s2) -> 
      let new_s2 = Stack.push x s2 in (s1, new_s2)

  let dequeue : 'a . 'a t -> ('a * 'a t) option = fun q ->
    if is_empty q then None else
      match q with (s1, s2) ->
        let s2_rev = append_rev s1 s2 in
        match (Stack.pop s2_rev) with None -> None | Some (value, s2_new_rev) ->
          let s2_new = append_rev s1 s2_new_rev in
          Some (value, (s1, s2_new))
end
