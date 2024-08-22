#pragma once
#include <glm/vec3.hpp>
#include "Globals/dllHeader.h"

class EXPORT MyPlane
{
public:
    glm::vec3 normal;
    glm::vec3 verA;
    glm::vec3 verB;
    glm::vec3 verC;

    float distance;
    MyPlane flipped() {return {this->normal,this->distance};}

    MyPlane(glm::vec3 inNormal, glm::vec3 inPoint);


    MyPlane(glm::vec3 inNormal, float d);


    MyPlane(glm::vec3 a, glm::vec3 b, glm::vec3 c);

    bool operator==(const MyPlane& right) const
    {
        return this->normal == right.normal && this->distance == right.distance;
    }

    bool operator!=(const MyPlane& right) const
    {
        return !(*this == right);
    }


    static MyPlane zero();


    void setNormalAndPosition(glm::vec3 inNormal, glm::vec3 inPoint);


    void set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);


    void flip();

    void translate(glm::vec3 translation);


    static MyPlane Translate(MyPlane plane, glm::vec3 translation);


    glm::vec3 closestPointOnPlane(glm::vec3 point);

    //vector generado entre el planoy el punto y la normal
    // si el angulo es menor a 90 es mayor

    float getDistanceToPoint(glm::vec3 point);

    //Calcula si un punto esta del lado "positivo" del Plano
    //El lado positivo es una convension
    // si la distancia hacia el punto es mayor a 0 devuelve positivo

    bool getSide(glm::vec3 point);
    
    bool sameSide(glm::vec3 inPt0, glm::vec3 inPt1);
};
