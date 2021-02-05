(* Bonus Problem *)
let rec stern_brocot_helper (l1,l2) (h1,h2) (m1,m2) = 
  if ((l1+h1)*m2 - (l2+h2)*m1) = 0 then []
  else 
    if ((l1+h1)*m2 - (l2+h2)*m1) < 0 then true :: stern_brocot_helper
    (l1+h1,l2+h2) (h1,h2) (m1,m2)
    else false :: stern_brocot_helper (l1,l2) (l1+h1,l2+h2) (m1,m2)


let stern_brocot x =
  stern_brocot_helper (0,1) (1,0) x
