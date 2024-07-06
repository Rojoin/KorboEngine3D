#pragma once
#include "Entity/Transform.h"
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class EXPORT Interface
{
public:
    Interface();
    void static ShowTransformEditor(Transform* transform);
};
