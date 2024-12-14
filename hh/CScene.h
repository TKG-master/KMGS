#pragma once
#include "GUI.h"
#include "TerrainLoder.h"

class Enemy;

class BoxObj;

class GoalObj;

//シーンクラスの原初 このシーンを親クラスにしてシーンを作っていく
class CScene
{
public:
	//コンストラクタ
	CScene();
	//デスストラタ
	~CScene();

	//オーバーライドする用
	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void UnInit();

	void CreateStage(TERRAIN_ID ID);

	DirectX::SimpleMath::Vector3 GetPlayerStartPos() { return PlayerStartPos; };

	DirectX::SimpleMath::Vector3 GetGoalPos() { return GoalPos; };

	std::vector<DirectX::SimpleMath::Vector3> GetEnemyStartPoss() { return ENEMYS; };

	static std::vector<std::vector<int>> GetMapData() { return map_data; };

	DirectX::SimpleMath::Vector3 GetCameraPos() { return CameraPos; };

	static std::vector<std::vector<int>> GetWanderingdata() { return Wandering_data; };


	DirectX::SimpleMath::Vector3 GetStartEasingPlayerPos() {
		StartEasingPlayerPos = PlayerStartPos;
		StartEasingPlayerPos.y += 500.0f;
		return StartEasingPlayerPos;
	}

	//ボックスの配列
	static std::vector<BoxObj*> BOXS;

	static BoxObj* floorBox;

protected:

	//敵の配列
	std::vector<DirectX::SimpleMath::Vector3> ENEMYS;
	// マップデータに関連する変数群
	static std::vector<std::vector<int>> map_data;
	//敵の徘徊ルートに関連するデータ
	static std::vector<std::vector<int>> Wandering_data;

	DirectX::SimpleMath::Vector3 PlayerStartPos;
	DirectX::SimpleMath::Vector3 StartEasingPlayerPos;
	DirectX::SimpleMath::Vector3 GoalPos;
	DirectX::SimpleMath::Vector3 CameraPos;


	// 各タイルのサイズ
	const float tile_size_x = SIZEX;
	const float tile_size_y = SIZEY;
	const float Bigtile_size_y = BIGSIZEY;
	const float tile_size_z = SIZEZ;

	float x_tile = ORIGIN_TILE_POS_X;
	float z_tile = ORIGIN_TILE_POS_Z;

	float total_width = 0.0f;
	float total_depth = 0.0f;

};

