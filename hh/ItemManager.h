#pragma once
#include "Book.h"


class ItemManager
{
private:
	std::vector<FBXMesh*> Items;


public:
	// �G��ǉ�����
	void AddItem(FBXMesh* Item);


};

