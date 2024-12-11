#pragma once

#include "gui/imgui.h"
#include "gui/backends/imgui_impl_win32.h"
#include "gui/backends/imgui_impl_dx11.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

//それぞれ必要なクラスの前方宣言
class PlayerTest;
class Camera;
class CCollision;
class Player;
class Enemy;
class easings;
class Radar;
class BoxObj;
class EnemyManager;

class GUI
{
public:
    GUI();
    ~GUI();

    void Update();
    void Draw();
    void PlayerUpdate(Player* player);
    void CameraUpdate(Camera* camera);
    void CollisionUpdate(CCollision& collision);
    void EnenyUpdate(EnemyManager* enemy);
    void RadarUpdate(Radar& radar);
    void BoxObjUpdate(BoxObj* Box);

    void flg(bool a[4]);

    int selectedEnemyIndex = -1; // グローバル変数として宣言



    void PlayerDraw(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 roa, DirectX::SimpleMath::Vector3 sca);

    void showFPS(int FPS);
    void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
    void UnInit();

    UINT sgui_g_ResizeWidth, sgui_g_ResizeHeight;
};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler
(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern GUI* gui;