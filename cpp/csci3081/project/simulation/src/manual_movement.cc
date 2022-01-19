// #include "manual_movement.h"
// #include <math.h>
//   // need to make some kind of getter in webapp picojson::object* keys similar to web* keys
// ManualMovement::ManualMovement(web* keys, Vector3 current, double direction, double dt, double speed)
//     : keys(k), current(curr), direction(dir), dt(d) speed(sp) {}

// Vector3 ManualMovement::GetPosition() { return current; }
// Vector3 ManualMovement::GetVelocity() { return velocity; }


// Vector3 ManualMovement::UpdateVelocity(double d, Vector3 curr, Vector3 tar, double time) {
//   // confused about whether I need this or not because in setJoystick could just have velocity = Vector3(x,y,z);
//   // reference lecture 14
//   current = curr;
//   target = tar;
//   dt = d;
//   // calculate direction d = target-current
//   Vector3 direction = target - current;
//   // normalize direction d= d/|d|
//   direction = direction.Normalize();
//   // calculate velocity v = d*speed
//   velocity = direction * speed;
//   return velocity;
// }

// bool ManualMovement::isMoving() {
//   // check if iskeydown for any of the manual movement buttons is true
//   if (get_web()->IsKeyDown("ArrowRight") == true||
//         get_web()->IsKeyDown("ArrowLeft") == true||
//         get_web()->IsKeyDown("ArrowUp") == true||
//         get_web()->IsKeyDown("ArrowDown") == true||
//         get_web()->IsKeyDown("w") == true||
//         get_web()->IsKeyDown("a") == true||
//         get_web()->IsKeyDown("s") == true||
//         get_web()->IsKeyDown("d") == true){
//             return true;
//         }
//         return false;
// }
// void move(){
//   // again need to make some kind of getter function for the webapp, will call this by get_web
//   setJoystick(
//         get_web()->IsKeyDown("ArrowRight") ? 1 : (get_web()->IsKeyDown("ArrowLeft") ? -1 : 0),
//         get_web()->IsKeyDown("ArrowUp") ? 1 : (get_web()->IsKeyDown("ArrowDown") ? -1 : 0),
//         get_web()->IsKeyDown("w") ? 1 : (get_web()->IsKeyDown("s") ? -1 : 0),
//         get_web()->IsKeyDown("a") ? 1 : (get_web()->IsKeyDown("d") ? -1 : 0))
//   // update position (current) by current = current + velocity*dt 
//     current = current + velocity*dt;
//     }
// }
// void setJoystick(double x, double y, double z, double p){
//     direction[0] = x;
//     direction[1] = y;
//     direction[2] = z;
// }