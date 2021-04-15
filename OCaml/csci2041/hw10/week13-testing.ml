module type STACK =
sig
  type 'a t
  val empty : 'a t
  val is_empty : 'a t -> bool
  val push : 'a -> 'a t -> 'a t
  val pop : 'a t -> ('a * 'a t) option
end

module StackTesterCommons =
struct
  type recipe =
    | Empty
    | Push of int * recipe
    | Pop of recipe
  type property =
    | Is_empty of bool
    | Popping of int option
  type test = recipe * property
  exception Test_failure
end

module type STACK_TESTER =
sig
  type recipe = StackTesterCommons.recipe
  type property = StackTesterCommons.property
  type test = StackTesterCommons.test
  val run_test : test -> unit
end

module StackTester (S : STACK) : STACK_TESTER =
struct
  include StackTesterCommons

  let rec realize : recipe -> int S.t =
    fun r ->
    match r with
    | Empty -> S.empty
    | Push (x, r) -> S.push x (realize r)
    | Pop r ->
      begin
        match S.pop (realize r) with
        | None -> raise Test_failure
        | Some (_, s) -> s
      end

  let check : property -> int S.t -> unit =
    fun p s ->
    match p with
    | Is_empty b ->
      if S.is_empty s = b then () else raise Test_failure
    | Popping None ->
      begin
        match S.pop s with
        | None -> ()
        | _ -> raise Test_failure
      end
    | Popping (Some x) ->
      begin
        match S.pop s with
        | None -> raise Test_failure
        | Some (x', _) ->
          if x = x' then () else raise Test_failure
      end

  let run_test = fun (r, p) -> check p (realize r)
end
