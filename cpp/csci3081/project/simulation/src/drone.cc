#include "drone.h"
#include <iostream>

void Drone::Update(double dt){
    if(hasCamera) {
        if(search != nullptr ){
            Vector3 *newVector = search->Search(*GetPosition());
            *velocity = movement->UpdateVelocity(dt, *position, *newVector, elapsedTime);
            *direction = velocity->Normalize();
            *position = *position + (*velocity*dt);
            elapsedTime += dt;
            CameraUpdate(dt);
        } else {
            if(!patroling && !robotFound) { //goto to corner
                *velocity = movement->UpdateVelocity(dt, *position, Vector3(-110,2,63), 0);
                if(!movement->isMoving()) { //switch to patrol
                    SetMovementStartegy(new PatrolStrategy(*GetPosition(), speed));
                    patroling = true;
                }
            }else if(patroling && !robotFound) { //patrol
                *velocity = movement->UpdateVelocity(dt, *position, Vector3(0,0,0), elapsedTime);
            } else { //robot found
                *velocity = movement->UpdateVelocity(dt, *position, robotLocation, 0);
            }

            *direction = velocity->Normalize();
            *position = *position + (*velocity*dt);
            elapsedTime += dt;
            CameraUpdate(dt);
        }
    } else {
        if(movement != NULL) {
            *velocity = movement->UpdateVelocity(dt, *position, robotLocation, 0);
            *direction = velocity->Normalize();
            *position = *position + (*velocity*dt);
        }
    }
}

void Drone::CameraUpdate(double dt) {
    if(!hasCamera)
        return;

    if(!robotFound && camera->isFound()) { //switch to beeline
        robotFound = true;
        robotLocation = Vector3(camera->getRobotLocation().GetX(), camera->getRobotLocation().GetY(), camera->getRobotLocation().GetZ());
        SetMovementStartegy(new BeelineMovement(*position, robotLocation, speed));
    }

    cameraTime += dt;
    if(cameraTime >= 2.5){
        //std::cout << dt << std::endl;
        std::cout << "Photo: " << cameraTime << std::endl;
        cameraTime -= 2.5;
        camera->TakePicture();
    }
}

void Drone::SetRobotFound(Vector3 robotLocation, Vector3 hospitalLocation) {
    this->robotLocation = robotLocation;
}