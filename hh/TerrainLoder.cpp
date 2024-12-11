#include "TerrainLoder.h"
#include <fstream>
#include <sstream>

// CTerrainLoaderクラスのstaticメンバ変数の初期化
TerrainLoder* TerrainLoder::instance = nullptr;


TerrainLoder::TerrainLoder()
{
	// ファイルの数だけループ
	for (int i = 0; i < file_name.size(); i++)
	{
		// パスを完成させ、path配列に格納
		path.push_back(file_name[i].insert(0, "assets/Stage/"));
	}

	// ファイルの数だけループ
	for (int i = 0; i < Wandering_name.size(); i++)
	{
		// パスを完成させ、path配列に格納
		Wandering_path.push_back(Wandering_name[i].insert(0, "assets/Wandering/"));
	}

}

TerrainLoder::~TerrainLoder()
{

}

void TerrainLoder::CleanupSingleton()
{
	//インスタンスがあるなら解放する
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

TerrainLoder* TerrainLoder::GetInstance()
{
	// シングルトンが存在していないなら生成する
	if (!instance)
	{
		// シングルトンの生成
		instance = new TerrainLoder();
		//コールバックとして登録
		std::atexit(CleanupSingleton);
	}
	//唯一のインスタンスを返す
	return instance;
}

void TerrainLoder::LoadTerrainData(TERRAIN_ID stage)
{
	// 前に読み込まれた情報をクリアする
	map_info.clear();

	// 読み込んだデータを格納

	std::string line;

	// 指定されたcsvファイルを開く
	std::ifstream ifs_csv_file(path[(int)stage]);

	// ファイルが正常に開けているかチェック
	if (!ifs_csv_file.is_open())
	{
		int a = 0;
		return;
	}

	// データを読み込む
	while (getline(ifs_csv_file, line))
	{
		std::vector<int> num;
		std::stringstream linestream(line);
		std::string cell;
		// 行に ','が現れるまで繰り返す
		while(getline(linestream, cell, ','))
		{
			try {
				int nu = std::stoi(cell);
				num.push_back(nu);
			}
			catch (const std::invalid_argument)
			{

			}
		}
		map_info.push_back(num);
	}
	// ファイルを閉じる
	ifs_csv_file.close();
}

std::vector<std::vector<int>> TerrainLoder::GetTerrainData()
{
	return map_info;
}

void TerrainLoder::LoadWnderingData(TERRAIN_ID stage)
{
	// 前に読み込まれた情報をクリアする
	Wandering_info.clear();

	// 読み込んだデータを格納

	std::string line;

	// 指定されたcsvファイルを開く
	std::ifstream ifs_csv_file(Wandering_path[(int)stage]);

	// ファイルが正常に開けているかチェック
	if (!ifs_csv_file.is_open())
	{
		int a = 0;
		return;
	}

	// データを読み込む
	while (getline(ifs_csv_file, line))
	{
		std::vector<int> num;
		std::stringstream linestream(line);
		std::string cell;
		// 行に ','が現れるまで繰り返す
		while (getline(linestream, cell, ','))
		{
			try {
				int nu = std::stoi(cell);
				num.push_back(nu);
			}
			catch (const std::invalid_argument)
			{
				//情報をint型に変換できなかった時に通る
				int a = 0;
			}
		}
		Wandering_info.push_back(num);
	}

	// ファイルを閉じる
	ifs_csv_file.close();
}

std::vector<std::vector<int>> TerrainLoder::GetWnderingData()
{
	return Wandering_info;
}


