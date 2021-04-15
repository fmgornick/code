module MiniModularML =
struct
  type path = string list
  type 'a expression =
    | Value of 'a
    | Variable of path
  type 'a module_expression =
    | Structure of 'a structure
    | Module_path of path
  and 'a declaration =
    | Let of string * 'a expression
    | Module of string * 'a module_expression
    | Open of 'a module_expression
    | Include of 'a module_expression
  and 'a structure = 'a declaration list
end

module type ENVIRONMENT =
sig
  open MiniModularML
  type 'a t
  exception Unbound
  val empty : 'a t
  val lookup_value : path -> 'a t -> 'a
  val lookup_module : path -> 'a t -> 'a t
  val bind_value : string * 'a -> 'a t -> 'a t
  val bind_module : string * 'a t -> 'a t -> 'a t
  val append : 'a t -> 'a t -> 'a t
end

module type COMPILATION =
sig
  type 'a t
  val compile_program : 'a MiniModularML.structure -> 'a t
end

module Compilation (E : ENVIRONMENT) :
  COMPILATION with type 'a t = 'a E.t
=
struct
  open MiniModularML

  type 'a t = 'a E.t

  (* fill in the structure *)
end
