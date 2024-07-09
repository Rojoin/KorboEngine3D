#pragma once
#include <glm/vec3.hpp>


class Camera;
//Todo: Add to engine the frustum check and to the draw of each model
//https://learnopengl.com/code_viewer_gh.php?code=src/8.guest/2021/1.scene/1.scene_graph/scene_graph.cpp
//https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/entity.h
//https://learnopengl.com/Guest-Articles/2021/Scene/Frustum-Culling
struct Plane
{
   
    glm::vec3 normal = {0.f, 1.f, 0.f}; // unit vector
    
    float distance = 0.f; // Distance with origin
    
    Plane() = default;
    
    Plane(const glm::vec3& p1, const glm::vec3& norm);
   void setNormalAndDistance(glm::vec3 point, glm::vec3 normal);
    
    
    float getSignedDistanceToPlane(const glm::vec3& point) const;
};

struct Frustum
{
    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;

    void createFrustumFromCamera(Camera* cam, float aspect, float fovY, float zNear, float zFar);

};
