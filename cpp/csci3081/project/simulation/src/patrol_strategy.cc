#include "patrol_strategy.h"
#include <math.h>

PatrolStrategy::PatrolStrategy(Vector3 curr, double sp){
  speed = sp;
  current = curr;
}

Vector3 PatrolStrategy::GetPosition(){
  return current;
}

Vector3 PatrolStrategy::GetVelocity(){
  return velocity;
}

Vector3 PatrolStrategy::UpdateVelocity(double dt, Vector3 current, Vector3 target, double time){
  Vector3 direction;
  
  double t = time / 9.5;
  double s = 13*sin(t);
  double x = abs(s/5);
  Vector3 d(x,0,s);
  direction = d;
  direction = direction.Normalize();
  
  velocity = direction*speed;
  distanceTraveled = velocity.GetMagnitude() * dt; 


   return velocity;
}

bool PatrolStrategy::isMoving(){
  //to do : update with completed logic once blob recognition is done
  //will return true if the robot is detected 
 return true;
}