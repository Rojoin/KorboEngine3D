#include "Interface.h"

#include <glm/gtc/type_ptr.hpp>


Interface::Interface()
{
}


void Interface::ShowTransformEditor(Transform* transform)
{
    if (ImGui::Begin("Transform Editor"))
    {
        static char nameBuffer[128];
        strcpy_s(nameBuffer, transform->name.c_str());
        std::string label = "Name" + std::to_string(transform->id);
        if (ImGui::InputText(label.c_str(), nameBuffer, IM_ARRAYSIZE(nameBuffer)))
        {
            transform->name = std::string(nameBuffer);
        }

        std::string pos = transform->name + "Position";
        std::string rotation = transform->name + "Rotation";
        std::string scale = transform->name + "Scale";
        if (transform->name != "Root")
        {
            ImGui::Text("Transform");
            glm::vec3 position = transform->localPosition;
            ImGui::DragFloat3(pos.c_str(), glm::value_ptr(position), 0.1f);
            transform->setLocalPosition(position);
            glm::vec3 rotationEuler = transform->localRotation;
            ImGui::DragFloat3(rotation.c_str(), glm::value_ptr(rotationEuler), 0.1f);
            transform->setLocalRotation(rotationEuler);
            glm::vec3 localScale = transform->localScale;
            ImGui::DragFloat3(scale.c_str(), glm::value_ptr(localScale), 0.1f);
            transform->setLocalScale(localScale);
        }
        ImGui::Separator();
        if (!transform->childs.empty())
        {
            std::string labelChilds = "Child Transforms" + std::to_string(transform->id);
            if (ImGui::TreeNode(labelChilds.c_str()))
            {
                for (auto* child : transform->childs)
                {
                    if (child != nullptr)
                    {
                        ShowTransformEditor(child);
                    }
                }
                ImGui::TreePop();
            }
        }

        ImGui::Separator();
    }
    ImGui::End();
}
