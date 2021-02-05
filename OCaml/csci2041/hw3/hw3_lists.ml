(* Problem 1 *)
let rec drop_last l =
  match l with
  | [] -> []
  | _ :: [] -> []
  | h :: t -> h :: drop_last t

(* Problem 2 *)
let rec add_index_helper i l =
  match l with
  | [] -> []
  | h :: t -> (i, h) :: add_index_helper (i+1) t

let add_index l =
  add_index_helper 0 l

(* Problem 3 *)
let rec generate f s = 
  match f s with
  | None -> s :: []
  | Some h -> s :: generate f h

(* Problem 4 *)
let rec delete_every_helper n i l =
  match l with
  | [] -> []
  | h :: t ->
      if i mod n = 0 
      then delete_every_helper n (i+1) t
      else h :: delete_every_helper n (i+1) t

let delete_every n l = delete_every_helper n 1 l
