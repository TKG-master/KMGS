#pragma once
#include <SimpleMath.h>
#include <string>
#include "CMesh.h"



class CObj3DMesh : public CMesh {
public:
	void Load(std::string filename);
};

