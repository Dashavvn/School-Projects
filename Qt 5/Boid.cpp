#include <cmath>
#include "Boid.h"

void Boid::seek(QVector3D target){
  QVector3D desiredVelocity = target-location; 
  if(desiredVelocity.length() > 0){
    desiredVelocity = desiredVelocity.normalized() * MAX_SPEED;
    force += desiredVelocity - velocity;
  }
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


void Boid::arrival(QVector3D target){
  QVector3D target_offset = target - location;
  theta = target_offset.length();
  float ramped_speed = MAX_SPEED * (theta / 30);
  float clipped_speed = min(ramped_speed, MAX_SPEED);
  QVector3D desired_velocity = (clipped_speed / theta) * target_offset;
  force += desired_velocity - velocity;
}


void Boid::cohesion(const vector<Boid>& boids){
  QVector3D  average(0,0,0);
  float total =0;
  for(int i =0 ; i < boids.size(); i++){
    if(boids[i].location.distanceToPoint(location) <5)
    {
      average += boids[i].location;	
      total +=1;
    }
  }
  average /= total;	
  seek(average);

}



float Boid::getAngle(){
  QVector3D direction = velocity.normalized();
  float angle =qRadiansToDegrees(atan2(direction.y(),direction.x()));
  angle -= 90;
  return angle;
}

/*
void Boid::wander()
{

  theta += rand()%7-3;

  theta =fmin(90,fmax(-90,theta));


  float turningRadius = 2;

  wanderTarget = QVector3D(theta,0,0); //turning radius instead of theta


  QVector3D center = location + velocity.normalized() *10;

  //get from inside main widget 
  QMatrix4x4 matrix;
  matrix.setToIdentity();
  matrix.rotate(0,0,0,1); // .5 to 1


  wanderTarget =  matrix*wanderTarget;

  seek(center + wanderTarget);
}
*/
void Boid::wander()
{

  theta += rand()%7-3;

  theta =fmin(90,fmax(-90,theta));

  wanderTarget = QVector3D(2,0,0); //turning radius instead of theta


  QVector3D center = location + velocity.normalized() *10;

  //get from inside main widget 

  QVector3D t =  center+wanderTarget;

  seek(t);
}
