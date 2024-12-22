#include "CScene.h"
#include "BoxObj.h"
#include "Enemy.h"
#include "GoalObj.h"
//static�̔z��
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

    //�}�b�v�̏��
	TerrainLoder::GetInstance()->LoadTerrainData(ID);
	map_data = TerrainLoder::GetInstance()->GetTerrainData();
    //�G�̜p�j���[�g�̏��
    TerrainLoder::GetInstance()->LoadWnderingData(ID);
    Wandering_data = TerrainLoder::GetInstance()->GetWnderingData();

    // �X�e�[�W�̑����Ƒ����s�����v�Z
    total_width = (map_data[0].size()) * tile_size_x;
    total_depth = (map_data.size() - 2) * tile_size_z;

    // floorBox�̃T�C�Y�ƈʒu��ݒ�
    floorBox = new BoxObj(total_width, 100.0f, total_depth, "assets\\Texture\\yuka.png");
    Vector3 floor_position(ORIGIN_TILE_POS_X + (total_width / 2.0f) - (tile_size_x / 2.0f),
        tile_size_y / 2.0 - 92.0f,
        ORIGIN_TILE_POS_Z - (total_depth / 2.0f) + (tile_size_z / 2.0f));
    floorBox->SetPosition(floor_position);
    floorBox->CollisionInit(floor_position, Vector3(total_width, tile_size_y / 2, total_depth));
    //floorBox->CollisionInit(floor_position, Vector3(0.0f,0.0f,0.0f));
    BOXS.push_back(floorBox);

    // �}�b�v�f�[�^�Ɋ�Â��ăX�e�[�W���\�z
    for (int z = 0; z < map_data.size(); ++z)
    {
        // y�����̃^�C����u���ʒu������
        z_tile = ORIGIN_TILE_POS_Z - (SIZEZ * z);
        for (int x = 0; x < map_data[z].size(); ++x)
        {
            // x�����̃^�C����u���ʒu������
            x_tile = ORIGIN_TILE_POS_X + (SIZEX * x);
            // �n�`ID�ɉ������I�u�W�F�N�g��z�u
            if (map_data[z][x] == 1) //Box
            {
                BoxObj* box = new BoxObj(tile_size_x, tile_size_y, tile_size_z , "assets\\Texture\\floor.png");
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
                // �G�̈ʒu��EnemyPositions�Ɋi�[
                ENEMYS.push_back(Vector3(x_tile, 0.0f, z_tile));
            }
            else if (map_data[z][x] == 4) //Goal
            {
                GoalPos = Vector3(x_tile, 50.0f, z_tile);
            }
            else if (map_data[z][x] == 5) //Camera
            {
                CameraPos = Vector3(x_tile, 1000.0f, z_tile);
            }
            else if (map_data[z][x] == 6) 
            {
                BoxObj* box = new BoxObj(tile_size_x, Bigtile_size_y, tile_size_z , "assets\\Texture\\RaderT.png");
                Vector3 position(x_tile, (Bigtile_size_y / 2), z_tile);
                box->SetPosition(position);
                box->CollisionInit(position, Vector3(tile_size_x, Bigtile_size_y, tile_size_z));
                BOXS.push_back(box);
            }
        }
    }



}
