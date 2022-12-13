#include "Boid.h"

void Boid::seek(QVector3D target){
    QVector3D desiredVelocity = target-location; 
    desiredVelocity = desiredVelocity.normalized() * MAX_SPEED;
    force += desiredVelocity - velocity;
}


void Boid::wander(){
    theta += rand()%7-3;

    theta = fmin(90,fmax(-90,theta));
    cout << theta << endl;

    float turningRadius = 8;
    QVector3D wanderTarget = QVector3D(turningRadius,0,0);



    //need better distance
    QVector3D center = velocity.normalized()*10;
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.rotate(theta+getAngle(),0,0,1);
    wanderTarget = matrix*wanderTarget;
    seek(center + wanderTarget);
}

float Boid::getAngle(){
    QVector3D direction = velocity.normalized();
    float angle = qRadiansToDegrees(atan2(direction.y(),direction.x()));
    angle -= 90;
    return angle;
}


void Boid::update(float dt){
    QVector3D acceleration = force/mass;
    if(acceleration.length() > 0){
        acceleration = acceleration.normalized()*min(acceleration.length(),MAX_FORCE);
    }
    velocity += acceleration*dt;
    if(velocity.length() > 0){
        velocity = velocity.normalized()*min(velocity.length(),MAX_SPEED);
    }
    location += velocity*dt;
    force = QVector3D(0,0,0);
}