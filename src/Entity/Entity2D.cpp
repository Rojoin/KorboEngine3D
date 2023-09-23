#include "Entity2D.h"

Entity2D::Entity2D(Renderer* renderer) : Entity(renderer)
{
    glm::vec3 vec(0.0f, 0.0f, 0.0f);
    model = glm::mat4(1.0f);

    model = glm::translate(model, vec);
    std::cout << vec.x << vec.y << vec.z << std::endl;
    model = glm::scale(model, glm::vec3(100, 100, 100));
}

Entity2D::~Entity2D()
{
    renderer->DeleteObjects(VAO, VBO, EBO);
}

void Entity2D::Draw()
{
    renderer->DrawEntity2D(VAO, indexSize, color, model);
}
