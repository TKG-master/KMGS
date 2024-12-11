#include "CObj3DMesh.h"
#include "ParesObj.h"
#include <iostream>

void CObj3DMesh::Load(std::string filename)
{
	GetVertex3D(filename.c_str(), m_vertices, m_indices);
}
