#pragma once
#include "CStaticMeshRenderer.h"
#include "CFBXMesh.h"

class CFBXMeshRenderer : public CStaticMeshRenderer {
public:
    void LoadFBX(const std::string& filename, const std::string& texturedirectory = "");
    void Draw();
};
