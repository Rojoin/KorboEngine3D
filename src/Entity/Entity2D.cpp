#include "Entity2D.h"

Entity2D::Entity2D(Renderer* renderer) : Entity(renderer)
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    TRS = glm::mat4(1.0f);
    
    vec = TRS * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    TRS = glm::rotate(TRS, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    TRS = glm::scale(TRS, glm::vec3(1, 0.5, 0.5)); 
}

Entity2D::~Entity2D()
{
    renderer->DeleteObjects(VAO, VBO, EBO);
}

void Entity2D::Draw() 
{
    renderer->DrawEntity2D(VAO, indexSize,color,TRS);
}
