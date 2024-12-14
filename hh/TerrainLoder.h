#pragma once
#include <vector>
#include <string>

// マップを構成するボックスのサイズ
#define SIZEX		(75.0f)
//小さいボックスY
#define SIZEY		(60.0f)
//大きいボックスY
#define BIGSIZEY	(100.0f);

#define SIZEZ		(75.0f)

//ゴールのサイズ
#define GSIZEX		(25.0f)
#define GSIZEY		(25.0f)
#define GSIZEZ		(25.0f)

//原点を開始とする
#define ORIGIN_TILE_POS_X	(0.0f)
#define ORIGIN_TILE_POS_Z	(0.0f)

// 地形データの識別子
enum class TERRAIN_ID
{
	STAGE_TEST,
	STAGE_1,
};


class TerrainLoder
{
private:

	// 唯一のインスタンスを格納するためのポインタ
	static TerrainLoder* instance;
	// ステージデータのファイル名
	std::vector<std::string> file_name =
	{
		"stage_Test.csv",
		"stageF_data.csv",
	};

	std::vector<std::string> Wandering_name =
	{
		"Stage_T.csv",
		"Stage_Fw.csv",
	};

	// 文字列連結で完成させたパスの情報を格納
	std::vector<std::string> path;
	// マップデータ保存用
	std::vector<std::vector<int>> map_info;
	// 文字列連結で完成させたパスの情報を格納
	std::vector<std::string> Wandering_path;
	// マップデータ保存用
	std::vector<std::vector<int>> Wandering_info;



	// コンストラクタ
	TerrainLoder();
	// デストラクタ
	~TerrainLoder();
	// アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();
public:

	// インスタンスを取得するためのメソッド
	static TerrainLoder* GetInstance();
	// 地形データの読み込み
	void LoadTerrainData(TERRAIN_ID stage);
	// 地形データの取得を行う
	std::vector<std::vector<int>> GetTerrainData();

	void LoadWnderingData(TERRAIN_ID stage);

	std::vector<std::vector<int>> GetWnderingData();






};

