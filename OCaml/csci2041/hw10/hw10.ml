module type TREE =
sig
  type 'a t
  val leaf : 'a t
  val branch : 'a t -> 'a -> 'a t -> 'a t
  val is_leaf : 'a t -> bool
  val left : 'a t -> 'a t option
  val right : 'a t -> 'a t option
  val root : 'a t -> 'a option
end

module TreeTesterCommons =
struct
  type recipe =
    | Leaf
    | Branch of recipe * int * recipe
    | Left of recipe
    | Right of recipe
  type property =
    | Is_leaf of bool
    | Has_left of bool
    | Has_right of bool
    | Has_root of int option
  type test = recipe * property
  exception Test_failure
end

module type TREE_TESTER =
sig
  type recipe = TreeTesterCommons.recipe
  type property = TreeTesterCommons.property
  type test = TreeTesterCommons.test

  val run_test : test -> unit
end

module TreeTester (T : TREE) : TREE_TESTER =
struct
  include TreeTesterCommons

  let rec realize : recipe -> int T.t =
    fun r ->
    match r with
    | Leaf -> T.leaf
    | Branch (left, root, right) -> T.branch (realize left) root (realize right)
    | Left r ->
      begin
        match T.left (realize r) with
        | None -> raise Test_failure
        | Some t -> t
      end
    | Right r ->
      begin
        match T.right (realize r) with
        | None -> raise Test_failure
        | Some t -> t
      end

  let check : property -> int T.t -> unit =
    fun p t ->
    match p with
    | Is_leaf b -> if T.is_leaf t = b then () else raise Test_failure
    | Has_left b ->
      begin
        match T.left t with
        | None -> if b = false then () else raise Test_failure
        | Some _ -> if b = true then () else raise Test_failure
      end
    | Has_right b ->
      begin
        match T.right t with
        | None -> if b = false then () else raise Test_failure
        | Some _ -> if b = true then () else raise Test_failure
      end
    | Has_root None ->
      begin
        match T.root t with
        | None -> ()
        | _ -> raise Test_failure
      end
    | Has_root (Some x) ->
      begin
        match T.root t with
        | None -> raise Test_failure
        | Some x' -> if x = x' then () else raise Test_failure
      end

  let run_test = fun (r, p) -> check p (realize r)
end
