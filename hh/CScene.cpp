#include "CScene.h"
#include "BoxObj.h"
#include "Enemy.h"
#include "GoalObj.h"
//staticの配列
std::vector<std::vector<int>> CScene::map_data;
std::vector<std::vector<int>> CScene::Wandering_data;
std::vector<BoxObj*> CScene::BOXS;
BoxObj* CScene::floorBox = nullptr;

CScene::CScene()
{

}

CScene::~CScene()
{
}

void CScene::Init()
{
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

void CScene::UnInit()
{
}

void CScene::CreateStage(TERRAIN_ID ID)
{

    ENEMYS.clear();

    //マップの情報
	TerrainLoder::GetInstance()->LoadTerrainData(ID);
	map_data = TerrainLoder::GetInstance()->GetTerrainData();
    //敵の徘徊ルートの情報
    TerrainLoder::GetInstance()->LoadWnderingData(ID);
    Wandering_data = TerrainLoder::GetInstance()->GetWnderingData();

    // 各タイルのサイズ
    const float tile_size_x = SIZEX;
    const float tile_size_y = SIZEY;
    const float Bigtile_size_y = BIGSIZEY;
    const float tile_size_z = SIZEZ;

    float x_tile = ORIGIN_TILE_POS_X;
    float z_tile = ORIGIN_TILE_POS_Z;

    // ステージの総幅と総奥行きを計算
    float total_width = (map_data[0].size() - 1) * tile_size_x;
    float total_depth = (map_data.size() - 2) * tile_size_z;

    // floorBoxのサイズと位置を設定
    floorBox = new BoxObj(total_width, 100.0f, total_depth, "assets\\MGfloor.jpeg");
    Vector3 floor_position(ORIGIN_TILE_POS_X + (total_width / 2.0f) - (tile_size_x / 2.0f),
        tile_size_y / 2.0 - 100.1f,
        ORIGIN_TILE_POS_Z - (total_depth / 2.0f) + (tile_size_z / 2.0f));
    floorBox->SetPosition(floor_position);
    floorBox->CollisionInit(floor_position, Vector3(total_width, tile_size_y, total_depth));
    BOXS.push_back(floorBox);

    // マップデータに基づいてステージを構築
    for (int z = 0; z < map_data.size(); ++z)
    {
        // y方向のタイルを置く位置を決定
        z_tile = ORIGIN_TILE_POS_Z - (SIZEZ * z);
        for (int x = 0; x < map_data[z].size(); ++x)
        {
            // x方向のタイルを置く位置を決定
            x_tile = ORIGIN_TILE_POS_X + (SIZEX * x);
            // 地形IDに応じたオブジェクトを配置
            if (map_data[z][x] == 1) //Box
            {
                BoxObj* box = new BoxObj(tile_size_x, tile_size_y, tile_size_z , "assets\\RaderT.png");
                Vector3 position(x_tile, (tile_size_y / 2), z_tile);
                box->SetPosition(position);
                box->CollisionInit(position, Vector3(tile_size_x, (tile_size_y / 2.0f), tile_size_z));
                BOXS.push_back(box);
            }
            else if (map_data[z][x] == 2) //Player
            {
                PlayerStartPos = Vector3(x_tile, 0.0f, z_tile);
            }
            else if (map_data[z][x] == 3) //Enemy
            {
                // 敵の位置をEnemyPositionsに格納
                ENEMYS.push_back(Vector3(x_tile, 0.0f, z_tile));
            }
            else if (map_data[z][x] == 4) //Goal
            {
                GoalPos = Vector3(x_tile, 25.0f, z_tile);
            }
            else if (map_data[z][x] == 5) //Camera
            {
                CameraPos = Vector3(x_tile, 1000.0f, z_tile);
            }
            else if (map_data[z][x] == 6) 
            {
                BoxObj* box = new BoxObj(tile_size_x, Bigtile_size_y, tile_size_z , "assets\\RaderT.png");
                Vector3 position(x_tile, (Bigtile_size_y / 2), z_tile);
                box->SetPosition(position);
                box->CollisionInit(position, Vector3(tile_size_x, Bigtile_size_y, tile_size_z));
                BOXS.push_back(box);
            }
        }
    }



}
