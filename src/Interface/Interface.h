#pragma once
#include "Entity/Transform.h"
#include "imgui/imgui.h"


class EXPORT Interface
{
public:
    Interface();
     Transform* selectedTransform = nullptr;
    int selectedIndex = -1;
   // void AddNodeToFlatList(Transform* node);
    void  ShowTransformEditor(Transform* transform);
   //void ShowHierarchyEditor(Transform* transform);
   //void InitializeNodeList(Transform* rootTransform);
};
