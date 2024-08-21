#include "Plane.h"

#include <glm/detail/func_geometric.inl>

MyPlane::MyPlane(glm::vec3 inNormal, glm::vec3 inPoint)
{
    this->normal = glm::normalize(inNormal);
    this->distance = glm::dot(inNormal, inPoint);
    verA = inPoint;
    verB = inPoint;
    verC = inPoint;
}

MyPlane::MyPlane(glm::vec3 inNormal, float d)
{
    this->normal = glm::normalize(inNormal);
    this->distance = d;
    verA = normal;
    verB = normal;
    verC = normal;
}

MyPlane::MyPlane(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    this->normal = glm::normalize(glm::cross(b - a, c - a));
    this->distance = -glm::dot(this->normal, a);
    verA = a;
    verB = b;
    verC = c;
}

MyPlane MyPlane::zero()
{ return {glm::vec3(0), 0}; }

void MyPlane::setNormalAndPosition(glm::vec3 inNormal, glm::vec3 inPoint)
{
    this->normal = glm::normalize(inNormal);
    this->distance = glm::dot(inNormal, inPoint);
}

void MyPlane::set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    this->normal = glm::normalize(glm::cross(b - a, c - a));
    this->distance = -glm::dot(this->normal, a);
}

void MyPlane::translate(glm::vec3 translation)
{
    distance += glm::dot(normal, translation);
}

MyPlane MyPlane::Translate(MyPlane plane, glm::vec3 translation)
{
    plane.translate(translation);
    return plane;
}

glm::vec3 MyPlane::closestPointOnPlane(glm::vec3 point)
{
    float pointToPlaneDistance = getDistanceToPoint(point);
    return point - (normal * pointToPlaneDistance);
}

float MyPlane::getDistanceToPoint(glm::vec3 point)
{
    return glm::dot(normal, point) + distance;
}

bool MyPlane::getSide(glm::vec3 point)
{
    return glm::dot(normal, point) + distance > 0.0F;
}

bool MyPlane::sameSide(glm::vec3 inPt0, glm::vec3 inPt1)
{
    float d0 = getDistanceToPoint(inPt0);
    float d1 = getDistanceToPoint(inPt1);
    return (d0 > 0.0f && d1 > 0.0f) ||
        (d0 <= 0.0f && d1 <= 0.0f);
}
void MyPlane::flip()
{
    this->normal = -normal;
    this->distance = -distance;
}
