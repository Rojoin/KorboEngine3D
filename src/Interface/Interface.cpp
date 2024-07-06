﻿#include "Interface.h"

#include <glm/gtc/type_ptr.hpp>


Interface::Interface()
{
}

void Interface::ShowTransformEditor(Transform* transform)
{
    
    ImGuiIO& io = ImGui::GetIO();
    
    if (ImGui::Begin("Transform Editor"))
    {
        ImGui::Text("Transform");

        ImGui::DragFloat3(" Position", glm::value_ptr(transform->localPosition), 0.1f);
        ImGui::DragFloat3(" Rotation", glm::value_ptr(transform->localRotation), 0.1f);
        ImGui::DragFloat3(" Scale", glm::value_ptr(transform->localScale), 0.1f);

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
