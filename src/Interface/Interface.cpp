#include "Interface.h"

#include <glm/gtc/type_ptr.hpp>


Interface::Interface()
{
}



void Interface::ShowTransformEditor(Transform* transform)
{
    
    if (ImGui::Begin("Transform Editor"))
    {
        if (transform->name.size() > 0)
        {
            ImGui::Text(transform->name.c_str());
        }

        std::string pos = transform->name+ "Position";
        std::string rotation = transform->name+ "Rotation";
        std::string scale = transform->name+ "Scale";
        ImGui::Text("Transform");
        ImGui::DragFloat3(pos.c_str(), glm::value_ptr(transform->localPosition), 0.1f);
        ImGui::DragFloat3(rotation.c_str(), glm::value_ptr(transform->localRotation), 0.1f);
        ImGui::DragFloat3(scale.c_str(), glm::value_ptr(transform->localScale), 0.1f);

        ImGui::Separator();
        if (ImGui::TreeNode("Child Transforms"))
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

        ImGui::Separator();
    }
    ImGui::End();
}
