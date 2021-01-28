let x : int * int = (2, 4) (* 2/4 *)

let y : int * int = (2, 3) (* 2/3 *)

(* `x_times_y` should give the multiplication of the two
   rational represented by `x` and `y`.

   Your code should not inline the actual values of `x`
   or `y`. In other words, even if we change the above
   bindings for `x` and `y` to something else, your code
   should still give the correct value. That is, you cannot
   hardcode `(1, 3)` as the answer. (The same rule was used
   in Homework 1.) Please fill in the code as if you do not
   know what `x` and `y` are except for their types.

   You do not have to simplify the rational. 2/4 is as good
   as 1/2 and -2/-6 is as good as 1/3. The denominators are
   guaranteed to be non-zero and do not worry about integer
   overflow.
 *)
let x_times_y : int * int = 
   match x with (x1,x2) ->
      match y with (y1,y2) -> (x1*y1,x2*y2)

(* `x_minus_y` should give the result of subtracting `y` from `x`.

   As above, your code should not inline the actual values
   of `x` or `y`.

   You do not have to simplify the rational. The denominators
   are guaranteed to be non-zero and do not worry about integer
   overflow.
 *)
let x_minus_y : int * int = 
   match x with (x1,x2) ->
      match y with (y1,y2) -> (x1*y2-y1*x2,x2*y2)

(* No need to fill in dynamic environments or typing contexts. *)
