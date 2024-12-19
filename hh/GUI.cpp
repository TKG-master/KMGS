#define _CRT_SECURE_NO_WARNINGS
#include "GUI.h"
#include "CTest.h"
#include "PlayerTest.h"
#include "Camera.h"
#include  "Player.h"
#include "easings.h"
#include "Type.h"
#include "IBehaviorNode.h"

const char* EStateTypeNames[] = {
    "Patrolling",  // 徘徊
    "Alerted",     // プレイヤーを見つけた
    "Investigating" // 中間地点のフェーズ（例：プレイヤーを見失った後の探索）
};


GUI::GUI()
{

}

GUI::~GUI()
{

}

void GUI::Update()
{

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

}

void GUI::Draw()
{


    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//プレイヤーのS R Tの情報
void GUI::PlayerUpdate(Player* player)
{
    if (!player) return;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Create a window
    ImGui::Begin("Player Debug");

    // プレイヤーのポジションを取得
    auto pos = player->GetPosition();
    auto roa = player->GetRotation();
    auto sca = player->GetScale();
    auto speed = player->GetSpeed();
    auto square = player->Getsquare();
    auto BlendeBool = player->GetAnimEndState();


    //階層構造
    if (ImGui::TreeNode("Transform")) {
        if (ImGui::TreeNode("Position")) {
            ImGui::SliderFloat("X", &pos.x, -500.0f, 500.0f);
            ImGui::InputFloat("Y", &pos.y, -500.0f, 500.0f);
            ImGui::SliderFloat("Z", &pos.z, -500.0f, 500.0f);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Rotation")) {
            ImGui::SliderFloat("Rot X", &roa.x, -DirectX::XM_PI, DirectX::XM_PI);
            ImGui::SliderFloat("Rot Y", &roa.y, -DirectX::XM_PI, DirectX::XM_PI);
            ImGui::SliderFloat("Rot Z", &roa.z, -DirectX::XM_PI, DirectX::XM_PI);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Scale")) {
            ImGui::SliderFloat("Scale X", &sca.x, 0.1f, 10.0f);
            ImGui::SliderFloat("Scale Y", &sca.y, 0.1f, 10.0f);
            ImGui::SliderFloat("Scale Z", &sca.z, 0.1f, 10.0f);
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Speed")) {
        ImGui::DragFloat("Speed", &speed, 0.1f, 0.0f, 10.0f);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Square3D")) {
        ImGui::SliderFloat("Square3D.X", &square.sizeX, 0.0f, 40.0f);
        ImGui::SliderFloat("Square3D.Y", &square.sizeY, 0.0f, 40.0f);
        ImGui::SliderFloat("Square3D.Z", &square.sizeZ, 0.0f, 40.0f);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("STAND"))
    {
        ImGui::Checkbox("stand", &BlendeBool);
        player->SetAnimEndState(BlendeBool); // 値を反映
        ImGui::TreePop();
    }


    // Update the player's position, rotation, scale, and speed
    player->SetPosition(pos);
    player->SetRotation(roa);
    player->SetScale(sca);
    player->SetSpeed(speed);
    player->Setsquare3D(square);

    // End the window
    ImGui::End();
}

void GUI::CameraUpdate(Camera* camera)
{
    if (!camera) return;

    // Create a window
    ImGui::Begin("Camera Debug");

    // カメラのポジションを取得
    auto pos = camera->GetCamPosition();
    auto focus = camera->GetCamforcas();
    auto speed = camera->GetSpeed();
    auto time = camera->GetT();

    if (ImGui::TreeNode("Transform")) {
        if (ImGui::TreeNode("Position")) {
            ImGui::SliderFloat("X", &pos.x, -500.0f, 500.0f);
            ImGui::SliderFloat("Y", &pos.y, -500.0f, 500.0f);
            ImGui::SliderFloat("Z", &pos.z, -500.0f, 500.0f);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Focus")) {
            ImGui::SliderFloat("Focus X", &focus.x, -5000.0f, 5000.0f);
            ImGui::SliderFloat("Focus Y", &focus.y, -5000.0f, 5000.0f);
            ImGui::SliderFloat("Focus Z", &focus.z, -5000.0f, 5000.0f);
            ImGui::TreePop();
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Speed")) {
        ImGui::DragFloat("Speed", &speed, 0.1f, 0.0f, 10.0f);
        ImGui::TreePop();
    }




    ImGui::SliderFloat("TTTT", &time, 0.0f, 1.0f);

    // Update the camera's position, focus, and speed
    camera->SetPosition(pos);
    camera->SetFoucus(focus);
    camera->SetSpeed(speed);
    camera->SetT(time);

    // End the window
    ImGui::End();

}

void GUI::CollisionUpdate(CCollision& collision)
{
    ImGui::Begin("Collision Info");

    // CCollision の情報を表示
    CCollision::SQUARE& square = collision.square;
    ImGui::Text("CenterX: %.2f", square.centerX);
    ImGui::Text("CenterZ: %.2f", square.centerZ);

    ImGui::SliderFloat("SizeX", &square.sizeX, 0.0f, 200.0f);
    ImGui::SliderFloat("SizeZ", &square.sizeZ, 0.0f, 200.0f);


    collision.SetCenterpoint(square.centerX,square.centerZ,square.sizeX,square.sizeZ);

    ImGui::End();
}

void GUI::EnenyUpdate(EnemyManager* Menemy)
{
    ImGui::Begin("Enemies");

    for (int i = 0; i < Menemy->GetEnemies().size(); ++i)
    {
        std::string treeNodeLabel = "Enemy " + std::to_string(i + 1);
        if (ImGui::CollapsingHeader(treeNodeLabel.c_str()))
        {
            Enemy* enemy = Menemy->GetEnemies()[i];
            if (!enemy) continue;

            auto forwr = enemy->forw;
            if (ImGui::TreeNode("forw"))
            {
                ImGui::SliderFloat3("x", &forwr.x, -1.0f, 1.0f);
                ImGui::SliderFloat3("y", &forwr.y, -1.0f, 1.0f);
                ImGui::SliderFloat3("z", &forwr.z, -1.0f, 1.0f);
                ImGui::TreePop();
            }

            // 位置の表示・編集
            DirectX::SimpleMath::Vector3 position = enemy->GetPosition();
            if (ImGui::TreeNode("Position"))
            {
                ImGui::SliderFloat3("Position", &position.x, -1200.0f, 1200.0f);
                enemy->SetPosition(position); // 値を反映
                ImGui::TreePop();
            }

            // 回転の表示・編集
            DirectX::SimpleMath::Vector3 rotation = enemy->GetRotation();
            if (ImGui::TreeNode("Rotation"))
            {
                ImGui::SliderFloat3("Rotation", &rotation.x, -100.0f, 100.0f);
                enemy->SetRotation(rotation); // 値を反映
                ImGui::TreePop();
            }

            // スケールの表示・編集
            DirectX::SimpleMath::Vector3 scale = enemy->GetScale();
            if (ImGui::TreeNode("Scale"))
            {
                ImGui::InputFloat3("Scale", &scale.x);
                enemy->SetScale(scale); // 値を反映
                ImGui::TreePop();
            }

            // 視線方向の表示・編集
            DirectX::SimpleMath::Vector3 forward = enemy->Getforward();
            if (ImGui::TreeNode("Forward"))
            {
                ImGui::SliderFloat3("Forward", &forward.x,-1.0f,1.0f);
                enemy->Setforward(forward); // 値を反映
                ImGui::TreePop();
            }

            // 位置の表示・編集
            DirectX::SimpleMath::Vector3 Sfor = enemy->GetSaveForward();
            if (ImGui::TreeNode("SaveForward"))
            {
                ImGui::InputFloat3("SaveForward", &Sfor.x);
                ImGui::TreePop();
            }

            // 視野角の表示・編集
            float fov = enemy->GetFov();
            if (ImGui::TreeNode("Field of View (FOV)"))
            {
                ImGui::SliderFloat("FOV", &fov, 0.0f, DirectX::XM_PI); // 0からPIラジアン (180度) の範囲で編集
                enemy->SetFov(fov); // 値を反映
                ImGui::TreePop();
            }

            // 視野距離の表示・編集
            float viewDistance = enemy->Getlength();
            if (ImGui::TreeNode("View Distance"))
            {
                ImGui::InputFloat("View Distance", &viewDistance);
                enemy->Setlength(viewDistance); // 値を反映
                ImGui::TreePop();
            }

            float viewX = enemy->Getview();
            if (ImGui::TreeNode("ViewX *"))
            {
                ImGui::InputFloat("ViewX *", &viewX, 0.0f, 100.0f);
                enemy->Setview(viewX);
                ImGui::TreePop();
            }

            bool test = enemy->GetTest();
            if (ImGui::TreeNode("Test"))
            {
                ImGui::Checkbox("Test", &test);
                enemy->SetTest(test); // 値を反映
                ImGui::TreePop();
            }

            float x = enemy->GetPoint().x;
            if (ImGui::TreeNode("Point"))
            {
                ImGui::SliderFloat("Point.x", &x, -100.0f, 100.0f);
                enemy->SetTest(x); // 値を反映
                ImGui::TreePop();
            }

            // Colorの表示・編集
            DirectX::SimpleMath::Color color = enemy->GetColor();
            if (ImGui::TreeNode("Color"))
            {
                float col[4] = { color.x, color.y, color.z, color.w }; // RGBA
                ImGui::ColorEdit4("Color", col);
                color = DirectX::SimpleMath::Color(col[0], col[1], col[2], col[3]);
                enemy->SetColor(color); // 値を反映
                ImGui::TreePop();
            }

            auto square = enemy->GetCollisionSize();
            if (ImGui::TreeNode("Square3D")) {
                ImGui::SliderFloat("Square3D.X", &square.sizeX, 0.0f, 40.0f);
                ImGui::SliderFloat("Square3D.Y", &square.sizeY, 0.0f, 40.0f);
                ImGui::SliderFloat("Square3D.Z", &square.sizeZ, 0.0f, 40.0f);
                ImGui::TreePop();
            }


            enemy->Setsquare3D(square);

            // ステートの表示・編集
            EStateType state = enemy->GetState();
            int stateIndex = static_cast<int>(state);
            if (ImGui::Combo("State", &stateIndex, EStateTypeNames, IM_ARRAYSIZE(EStateTypeNames)))
            {
                state = static_cast<EStateType>(stateIndex);
                enemy->SetState(state);
            }
        }
    }

    auto ray = Menemy->GetrayDistance();
    if (ImGui::TreeNode("rayDistance"))
    {
        ImGui::SliderFloat3("rayDistance", &ray.x, -0.0f, 10.0f);
        ImGui::TreePop();
    }
    Menemy->SetrayDistance(ray);

    float rayY = Menemy->GetrayY();
    if (ImGui::TreeNode("rayY"))
    {
        ImGui::InputFloat("rayY", &rayY, 0.0f, 40.0f);
        ImGui::TreePop();
    }
    Menemy->SetrayY(rayY);

    ImGui::End();
}

void GUI::RadarUpdate(Radar& radar)
{
    // ImGuiでグラフを描画
    ImGui::Begin("Radar");

    auto Center = radar.GetRadarCenter();
    auto X = radar.SaveANSx();
    auto Y = radar.SaveANSy();
    auto relativePos = radar.GetrelativePos();
    if (ImGui::TreeNode("m_RadarCenter"))
    {
        ImGui::SliderFloat("X", &Center.x, -500.0f, 500.0f);
        ImGui::SliderFloat("Y", &Center.y, -500.0f, 500.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("relativePos.x"))
    {
        ImGui::SliderFloat("relativePosX", &relativePos.x, -500.0f, 500.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("relativePos.y"))
    {
        ImGui::SliderFloat("relativePosY", &relativePos.y, -500.0f, 500.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("SaveANSX"))
    {
        ImGui::SliderFloat("X", &X, -500.0f, 500.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("SaveANSY"))
    {
        ImGui::SliderFloat("Y", &Y, -500.0f, 500.0f);
        ImGui::TreePop();
    }



    ImGui::End();
}

void GUI::BoxObjUpdate(BoxObj* Box)
{
    ImGui::Begin("Box");

    auto square = Box->GetCollisionSize();

    bool Hit = Box->GetHit(); 
    if (ImGui::TreeNode("Test"))
    {
        ImGui::Checkbox("Hit", &Hit);
        Box->SetHit(Hit); // 値を反映
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Square3D")) {
        ImGui::SliderFloat("Square3D.X", &square.sizeX, 0.0f, 100.0f);
        ImGui::SliderFloat("Square3D.Y", &square.sizeY, 0.0f, 100.0f);
        ImGui::SliderFloat("Square3D.Z", &square.sizeZ, 0.0f, 100.0f);
        ImGui::TreePop();
    }

    Box->Setsquare3D(square);

    ImGui::End();
}

void GUI::flg(bool a[4])
{
    ImGui::Begin("isHit A");

    for (int i = 0; i < 4; ++i) {
        // bool型の値を "true" もしくは "false" という文字列に変換して表示
        ImGui::Text("isHit[%d]: %s", i, a[i] ? "true" : "false");
    }

    ImGui::End();
}






//void GUI::PlayerUpdate(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 roa, DirectX::SimpleMath::Vector3 sca)
//{
//    ImGui_ImplDX11_NewFrame();
//    ImGui_ImplWin32_NewFrame();
//    ImGui::NewFrame();
//
//
//    // Create a window
//    ImGui::Begin("Player Debug");
//
//    // Position controls
//    ImGui::Text("Position");
//    ImGui::SliderFloat("X", &pos.x, -200.0f, 200.0f);
//    ImGui::SliderFloat("Y", &pos.y, -200.0f, 200.0f);
//    ImGui::SliderFloat("Z", &pos.z, -200.0f, 200.0f);
//
//    // Rotation controls
//    ImGui::Text("Rotation");
//    ImGui::SliderFloat("Rot X", &roa.x, -DirectX::XM_PI, DirectX::XM_PI);
//    ImGui::SliderFloat("Rot Y", &roa.y, -DirectX::XM_PI, DirectX::XM_PI);
//    ImGui::SliderFloat("Rot Z", &roa.z, -DirectX::XM_PI, DirectX::XM_PI);
//
//    // Scale controls
//    ImGui::Text("Scale");
//    ImGui::SliderFloat("Scale X", &sca.x, 0.1f, 10.0f);
//    ImGui::SliderFloat("Scale Y", &sca.y, 0.1f, 10.0f);
//    ImGui::SliderFloat("Scale Z", &sca.z, 0.1f, 10.0f);
//
//    // End the window
//    ImGui::End();
//
//}

void GUI::PlayerDraw(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 roa, DirectX::SimpleMath::Vector3 sca)
{

}

//float GUI::Camera(float CamZoomSpeed)
//{
//
//    static float Speed = CamZoomSpeed;
//    static char text1[20] = "";
//
//    ImGui::Text("CamZoomSpeed");
//
//    //ImGui::Text("fps: %.2f", getFrameRate());
//    ImGui::DragFloat("CamZoomSpeed", &Speed, 0.0f, 1.0f);
//    ImGui::InputText("textbox 1", text1, sizeof(text1));
//    if (ImGui::Button("CamSpeedInit")) {
//        Speed = 0.3f;
//    }
//
//    //ImGui::SetWindowPos(windowPos);
//
//    ImGui::Text("fugafuga");
//
//    return CamZoomSpeed;
//
//}

//引数は位置・視点　スケール　カメラの速さ
//void GUI::CameraUpdate(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 foc,float CamZoomSpeed)
//{
//    ImGui::Begin("Camera");
//
//    pos =CameraPos(pos);
//    foc = CameraRoa(foc);
//    Camera(CamZoomSpeed);
//
//    // End the window
//    ImGui::End();
//
//
//}

void GUI::showFPS(int FPS)
{
    // FPS表示ウィンドウの作成
    ImGui::Begin("FPS Display");

    // FPSの表示
    ImGui::Text("FPS: %d", FPS);

    // ウィンドウの終了
    ImGui::End();
}

void GUI::Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
    ImGui::CreateContext();

    // 日本語対応
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts
        ->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, context);
    ImGui_ImplDX11_CreateDeviceObjects();



    /*ImGui::SetNextWindowSize(ImVec2(800, 100), ImGuiCond_Always);*/




}

void GUI::UnInit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
