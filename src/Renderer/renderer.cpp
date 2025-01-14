#include "renderer.h"

#include <glm/gtc/type_ptr.hpp>

#include "Globals/Vec4.h"


#define STB_IMAGE_IMPLEMENTATION
#include <array>
#include <format>
#include <format>

#include "Frustrum.h"
#include "Camera/Camera.h"
#include "Mesh/BasicMesh.h"
#include "Mesh/BasicMesh.h"
#include "Mesh/BasicMesh.h"
#include "Mesh/BasicMesh.h"
#include "Mesh/BasicMesh.h"
#include "Planes/Plane.h"
#include "Shader/Material.h"
#include "stb/stb_image.h"

Renderer::Renderer(Window* window, GLbitfield mask)
{
    this->GLFWW = window;
    this->mask = mask;
    ambientStrengh = 0.5f;
    cout << "Renderer Created" << endl;
}


Renderer::Renderer(Window* window, Camera* camera)
{
    this->GLFWW = window;
    this->mask = GL_COLOR_BUFFER_BIT;
    this->camera = camera;
    projection = camera->getProjectionMatrix(window->getWidth(), window->getHeight());
    ambientStrengh = 0.5f;

    globalLight = new DirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f),
                                     glm::vec3(.4f, .4f, .4f),
                                     glm::vec3(.4f, 0.4f, 0.4f),
                                     glm::vec3(0.5f, 0.5f, 0.5f));
    flashLight = new SpotLight();
    pointLight = new PointLight();
    view = camera->getViewMatrix();

    shaderShape = new Shader("../res/shaders/BasicShader.shader");
    shaderSprite = new Shader("../res/shaders/TextureShader.shader");
    shaderLightning = new Shader("../res/shaders/LightningShader.shader");
    shaderBasicModel = new Shader("../res/shaders/ModelLoading.shader");
    shaderLines = new Shader("../res/shaders/LinesShader.shader");
    createTextureBinder(textureDefault, "../res/images/DefaultSprite.png");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glEnable(GL_SAMPLE_ALPHA_TO_ONE);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND); //Transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);

    shaderShape->bind();
    shaderSprite->bind();
    shaderLightning->bind();
    cout << "Renderer Created" << endl;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
}

Renderer::~Renderer()
{
    cout << "Renderer Deleted" << endl;
    delete globalLight;
    delete pointLight;
    delete flashLight;
    delete shaderShape;
    delete shaderLines;
    delete shaderSprite;
    delete shaderLightning;
    delete shaderBasicModel;
}

void Renderer::DeleteObjects(unsigned& VAO, unsigned& VBO, unsigned& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::EndDrawing()
{
    glfwSwapBuffers(GLFWW->getWindow());
    glfwPollEvents();
}

void Renderer::BeginDrawing()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::SetWindow(Window* window) { GLFWW = window; }

void Renderer::Setbitfield(GLbitfield mask) { this->mask = mask; }

GLbitfield Renderer::Getbitfield() { return this->mask; }


void Renderer::createVecBuffer(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                               unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, atribVertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Renderer::createVecBufferWithNormals(float* positions, int* indices, int positionsSize, int atribNormalSize,
                                          int atribVertexSize, int indicesSize, unsigned& VAO, unsigned& VBO,
                                          unsigned& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, atribNormalSize, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Renderer::createVecBufferWithNormalsUV(float* positions, int* indices, int positionsSize, int atribNormalSize,
                                            int atribVertexSize, int indicesSize, int atribUVSize, unsigned& VAO,
                                            unsigned& VBO,
                                            unsigned& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, atribNormalSize, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, atribUVSize, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Renderer::createVecBufferWithUV(float* positions, int* indices, int positionsSize, int indicesSize,
                                     int atribVertexSize,
                                     unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, int atribColorSize,
                                     int atribUVSize)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, atribColorSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, atribUVSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                          (void*)((7) * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Renderer::createTextureBinder(unsigned int& textureId, const char* imagePath)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int width, height, nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (nrChannels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 3)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    else if (nrChannels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
                     data);
    else if (nrChannels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Image couldn't be loaded.";
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Renderer::createTextureBinder(unsigned int& textureId, const char* imagePath, int& width, int& height)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (nrChannels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 3)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    else if (nrChannels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
                     data);
    else if (nrChannels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Image couldnt be loaded.";
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Renderer::createTextureBinder(unsigned int& textureId, const char* imagePath, int& width, int& height,
                                   GLint textureWrapping)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapping);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureWrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureWrapping);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (nrChannels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 3)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    else if (nrChannels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
                     data);
    else if (nrChannels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Image couldnt be loaded.";
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Renderer::DrawEntity(unsigned int VAO, int sizeIndices, Vec4 color, glm::mat4x4 model) const
{
    shaderShape->bind();


    glm::mat4 PVM = projection * view * model;
    shaderShape->SetMat4("transform", PVM);

    shaderShape->SetVec4("colorTint", glm::vec4(color.x, color.y, color.z, color.w));
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawSprite2D(unsigned VAO, int sizeIndices, Vec4 color, glm::mat4x4 model, unsigned& texture) const
{
    shaderSprite->bind();

    glm::mat4 PVM = projection * view * model;
    shaderSprite->SetMat4("MVP", PVM);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(nullptr));
}

void Renderer::DrawEntity3D(unsigned VAO, int sizeIndices, Vec4 color, glm::mat4x4 model, Material material,
                            unsigned& texture, bool isUsingTexture)
{
    shaderLightning->bind();
    shaderLightning->SetMat4("model", model);
    shaderLightning->SetMat4("view", view);
    shaderLightning->SetMat4("projection", projection);


    shaderLightning->SetVec3("viewPos", camera->Position);


    // directional light
    shaderLightning->SetDirectionalLight("dirLight", globalLight);
    // point light 1
    shaderLightning->SetPointLight("pointLights[0]", pointLight);

    // spotLight
    flashLight->setDirAndPos(camera->Front, camera->getCameraPosition());
    shaderLightning->SetSpotLight("spotLight", flashLight);


    // material properties
    shaderLightning->SetMaterial("material", material);

    shaderLightning->SetVec3("material.ambient", material.ambient);
    shaderLightning->SetVec3("material.diffuse", material.diffuse);
    shaderLightning->SetVec3("material.specular", material.specular);
    shaderLightning->SetFloat("material.shininess", material.shininess);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, isUsingTexture ? texture : textureDefault);
    // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawModel3D( glm::mat4x4 model, unsigned VAO, std::vector<unsigned int> indices,
                           std::vector<Texture> textures)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalsNr = 1;
    unsigned int heightNr = 1;
    unsigned int baseColorNr = 1;
    unsigned int metalnessNr = 1;
    unsigned int roughnessNR = 1;

    shaderBasicModel->bind();
    shaderBasicModel->SetMat4("model", model);
    shaderBasicModel->SetMat4("view", view);
    shaderBasicModel->SetMat4("projection", projection);

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_baseColor")
            number = std::to_string(baseColorNr++);
        else if (name == "texture_normals")
            number = std::to_string(normalsNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);
        else if (name == "texture_metalness")
            number = std::to_string(metalnessNr++);
        else if (name == "texture_roughness")
            number = std::to_string(roughnessNR++);

        shaderBasicModel->SetInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    shaderBasicModel->SetVec3("viewPos", camera->Position);

    // directional light
    shaderBasicModel->SetDirectionalLight("dirLight", globalLight);
    // point light 1
    shaderBasicModel->SetPointLight("pointLights[0]", pointLight);

    flashLight->setDirAndPos(camera->Front, camera->getCameraPosition());
    shaderBasicModel->SetSpotLight("spotLight", flashLight);


    // material properties

    // shader->SetMaterial("material", RUBY);

    shaderBasicModel->SetFloat("material.shininess", BRONZE.shininess);
    shaderBasicModel->SetFloat("material.metalness", BRONZE.shininess);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
void Renderer::DrawLinesAABB( glm::mat4x4 model,  std::vector<glm::vec3> vertices)
{
    const GLuint indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0, // Bottom face
        4, 5, 5, 6, 6, 7, 7, 4, // Top face
        0, 4, 1, 5, 2, 6, 3, 7  // Vertical edges
    };
    GLuint VAO, VBO,EBO;
    shaderLines->bind();
    shaderLines->SetMat4("model", model);
    shaderLines->SetMat4("view", view);
    shaderLines->SetMat4("projection", projection);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Use the shader program
  
    // Draw the bounding box as lines
    glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAO);
}
void Renderer::DrawFrustum(glm::mat4x4 viewProjectionMatrix, Frustum frustum)
{

    std::vector<glm::vec3> vertices = {
        -frustum.nearFace.normal * frustum.nearFace.distance,   // near bottom left
        frustum.nearFace.normal * frustum.nearFace.distance,    // near bottom right
        frustum.rightFace.normal * frustum.rightFace.distance,  // near top right
        -frustum.leftFace.normal * frustum.leftFace.distance,   // near top left
        -frustum.farFace.normal * frustum.farFace.distance,     // far bottom left
        frustum.farFace.normal * frustum.farFace.distance,      // far bottom right
        frustum.rightFace.normal * frustum.rightFace.distance + frustum.farFace.normal * frustum.farFace.distance, // far top right
        -frustum.leftFace.normal * frustum.leftFace.distance + frustum.farFace.normal * frustum.farFace.distance  // far top left
    };

    // Define indices for drawing the frustum as lines
    const GLuint indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0,  // near plane
        4, 5, 5, 6, 6, 7, 7, 4,  // far plane
        0, 4, 1, 5, 2, 6, 3, 7   // connections between near and far planes
    };

    GLuint VAO, VBO, EBO;
    shaderLines->bind();
    shaderLines->SetMat4("model", glm::mat4(1.0f)); // Identity matrix since frustum is already in world space
    shaderLines->SetMat4("view", glm::mat4(1.0f));  // Identity matrix since frustum is already in world space
    shaderLines->SetMat4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw the frustum as lines
    glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}
void Renderer::DrawPlane(Plane* plane)
{
   glm::vec3 planeCenter = plane->normal * -plane->distance;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Avoids the case when the plane is parallel to the Y-axis
    if (plane->normal == up) {
        up = glm::vec3(1.0f, 0.0f, 0.0f);
    }

    glm::vec3 right = glm::normalize(glm::cross(plane->normal, up));
    up = glm::normalize(glm::cross(right, plane->normal));

    float planeSize = 100.0f; // Adjust the size of the plane as needed

    std::vector<glm::vec3> planeVertices = {
        planeCenter + (right * planeSize) + (up * planeSize),    // top right
        planeCenter + (right * planeSize) - (up * planeSize),    // bottom right
        planeCenter - (right * planeSize) - (up * planeSize),    // bottom left
        planeCenter - (right * planeSize) + (up * planeSize)     // top left
    };

    const GLuint planeIndices[] = {
        0, 1, 2, 2, 3, 0   // forming two triangles for a quad
    };

    GLuint VAO, VBO, EBO;
    shaderLines->bind();
    shaderLines->SetMat4("model", glm::mat4(1.0f)); // Assuming identity model matrix for simplicity
    shaderLines->SetMat4("view", view);             // Using pre-defined view matrix
    shaderLines->SetMat4("projection", projection); // Using pre-defined projection matrix

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(glm::vec3), &planeVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw the plane as triangles
    glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Draw the normal
    glm::vec3 normalStart = planeCenter;
    glm::vec3 normalEnd = planeCenter + plane->normal * 50.0f; // Lengthen the normal line

    std::vector<glm::vec3> normalLine = { normalStart, normalEnd };

    GLuint normalVBO;
    glGenBuffers(1, &normalVBO);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normalLine.size() * sizeof(glm::vec3), &normalLine[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw the normal as a line
    glDrawArrays(GL_LINES, 0, normalLine.size());

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &normalVBO);
}
