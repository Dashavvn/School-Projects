#ifndef BOID__H
#define BOID__H

#include <QVector3D>
#include <QMatrix4x4>
#include <iostream>
#include <QtMath>

using namespace std;

struct Boid{
    QVector3D velocity;
    QVector3D location;
    float mass = 1;
    float MAX_SPEED = 12.0f;
    float MAX_FORCE = 20.0f;
    QVector3D force;
    float theta = 0;
    QVector3D wanderTarget;
    

    void seek(QVector3D target);
    void update(float dt);
    void wander();
    float getAngle();
    void cohesion(const vector<Boid>& boids);    
    void arrival(QVector3D target);
};


#endif
