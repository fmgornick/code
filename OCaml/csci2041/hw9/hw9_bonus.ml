module type ENVIRONMENT =
sig
  type 'a t

  exception Unbound

  val empty : 'a t

  val lookup_value : string list -> 'a t -> 'a
  val lookup_module : string list -> 'a t -> 'a t

  val bind_value : string * 'a -> 'a t -> 'a t
  val bind_module : string * 'a t -> 'a t -> 'a t

  val append : 'a t -> 'a t -> 'a t
end

module Environment : ENVIRONMENT =
struct
  (* The following type is given as a suggestion. You do not have to use it!
   * We use the "and" keyword (not covered in the lectures) because 'a t and
   * 'a entry are mutually recursive. You do not need any fancy mutually
   * recursive types, but this is a solution that is too good to pass. *)
  type 'a t = (string * 'a entry) list
  and 'a entry = Value of 'a | Module of 'a t

  (* fill in the structure *)
end
