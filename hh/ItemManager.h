#pragma once
#include "Book.h"


class ItemManager
{
private:
	std::vector<FBXMesh*> Items;


public:
	// 敵を追加する
	void AddItem(FBXMesh* Item);


};

