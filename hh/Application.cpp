//Includes
#include <chrono>
#include <thread>
#include "Application.h"
#include "fpscontrol.h"
#include "renderer.h"
#include "Camera.h"
#include "Field.h"
#include "CBoxMesh.h"
#include "GUI.h"
#include "Input.h"
#include "Polygon2D.h"
#include "CSceneManager.h"
#include "GameObject.h"

// Constant Values.
const auto ClassName = TEXT("KoMGS");                      //ウィンドウクラス名
const auto WindowName = TEXT("KoMGS");    //ウィンドウ名



// Class Static
HINSTANCE  Application::m_hInst;        // インスタンスハンドル
HWND       Application::m_hWnd;         // ウィンドウハンドル
uint32_t   Application::m_Width;        // ウィンドウの横幅
uint32_t   Application::m_Height;       // ウィンドウの縦幅

//imguiのメモリ確保
GUI* gui = new GUI();

//コンストラクタ
Application::Application(uint32_t width, uint32_t height)
{ 
    m_Height = height;
    m_Width = width;
    timeBeginPeriod(1);
}

//デストラクタ
Application::~Application()
{ 
    timeEndPeriod(1);
}

//実行
void Application::Run()
{
    if (InitApp())
    { 
        MainLoop(); 
    }

    TermApp();
}

//初期化処理です.
bool Application::InitApp()
{
    // ウィンドウの初期化.
    if (!InitWnd())
    { 
        return false; 
    }

    // 正常終了.
    return true;
}

//終了処理です
void Application::TermApp()
{
    // ウィンドウの終了処理
    TermWnd();
}

//ウィンドウの初期化処理です
bool Application::InitWnd()
{
    // インスタンスハンドルを取得
    auto hInst = GetModuleHandle(nullptr);
    if (hInst == nullptr)
    { 
        return false; 
    }

    // ウィンドウの設定
    WNDCLASSEX wc = {};
    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = WndProc;
    wc.hIcon            = LoadIcon(hInst, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(hInst, IDC_ARROW);
    wc.hbrBackground    = GetSysColorBrush(COLOR_BACKGROUND);
    wc.lpszMenuName     = nullptr;
    wc.lpszClassName    = ClassName;
    wc.hIconSm          = LoadIcon(hInst, IDI_APPLICATION);

    // ウィンドウの登録
    if (!RegisterClassEx(&wc))
    { return false; }

    // インスタンスハンドル設定
    m_hInst = hInst;

    // ウィンドウのサイズを設定
    RECT rc = {};
    rc.right  = static_cast<LONG>(m_Width);
    rc.bottom = static_cast<LONG>(m_Height);

    // ウィンドウサイズを調整
    auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    AdjustWindowRect(&rc, style, FALSE);

    // ウィンドウを生成
    m_hWnd = CreateWindowEx(
        0,
        ClassName,
        WindowName,
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rc.right  - rc.left,
        rc.bottom - rc.top,
        nullptr,
        nullptr,
        m_hInst,
        nullptr);

    if (m_hWnd == nullptr)
    { return false; }
 
    // ウィンドウを表示
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    // ウィンドウを更新
    UpdateWindow(m_hWnd);

    // ウィンドウにフォーカスを設定
    SetFocus(m_hWnd);

    // 正常終了.
    return true;
}

//ウィンドウの終了処理
void Application::TermWnd()
{
    // ウィンドウの登録を解除
    if (m_hInst != nullptr)
    { UnregisterClass(ClassName, m_hInst); }

    m_hInst = nullptr;
    m_hWnd  = nullptr;
}

//メインループです
void Application::MainLoop()
{
    MSG msg = {};

    // FPS表示用変数
    int fpsCounter = 0;
    long long oldTick = GetTickCount64();//現在時間を保存
    long long nowTick = oldTick; // 現在時間取得用

    // FPS固定用変数
    LARGE_INTEGER liWork; // 関数から値を受け取る用
    long long frequency; // 計測精度
    // 計測精度を取得
    QueryPerformanceFrequency(&liWork);
    frequency = liWork.QuadPart; // １秒あたりの解像度が入る
    // １フレームあたりのカウント値を計算
    long long numCount_1frame = frequency / 60; // 60FPSで計算
    // 現在時間（単位：カウント）を取得
    QueryPerformanceCounter(&liWork);
    long long oldCount = liWork.QuadPart;
    long long nowCount = oldCount;

    //入力処理の初期化
    Input::Get()->Initialize(m_hWnd, m_hInst);

    // FPS調整クラス
    FPS fpsrate(60);

    Renderer::Init();

    CSceneManager::GetInstance()->Init();

    HRESULT hr;
    hr = XA_Initialize();

    //imguiの初期化
    gui->Init(m_hWnd, Renderer::GetDevice(), Renderer::GetDeviceContext());

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

            // 1/60秒経過したか？
            QueryPerformanceCounter(&liWork);
            nowCount = liWork.QuadPart; // 現在時間を取得（単位：カウント）

            if (nowCount >= oldCount + numCount_1frame)
            {
                Renderer::Begin();

                //キーボードの入力のアップデート
                Input::Get()->Update();
                //シーンマネージャーのアップデート
                CSceneManager::GetInstance()->Update();
                CSceneManager::GetInstance()->Draw();

                fpsCounter++; // ゲームループ実行回数をカウント＋１
                oldCount = nowCount;

               //gui->Draw();

                Renderer::End();

            }

            nowTick = GetTickCount64(); // 現在時間取得
            // １秒経過したか？
            if (nowTick >= oldTick + 1000)
            {
                // FPSを表示する
                char str[32];
                wsprintfA(str, "FPS=%d", fpsCounter);
                SetWindowTextA(m_hWnd, str);
                // カウンターをリセット
                fpsCounter = 0;
                oldTick = nowTick;
            }

            uint64_t delta_time = 0;

        }
    }
    //シーンマネージャーの終了処理
    CSceneManager::GetInstance()->CleanupSingleton();
    //imguiの終了処理
    gui->UnInit();
    XA_Release();
    delete gui;


    // 描画終了処理
    Renderer::Uninit();
}

//ウィンドウプロシージャ
LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp)) {

        return true;
    }
    switch(msg)
    {
        case WM_DESTROY:
            { 
                PostQuitMessage(0); 
            }
            break;
        case WM_CLOSE:  // xボタンが押されたら
            DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
            break;

            // キーが押されたイベント
        case WM_KEYDOWN:
            break;

            // キーが離されたイベント
        case WM_KEYUP:
            break;

        default:
            // 上のcase以外の場合の処理を実行
            return DefWindowProc(hWnd, msg, wp, lp);
            break;

        //default:
        //    { /* DO_NOTHING */ }
        //    break;
    }

    return DefWindowProc(hWnd, msg, wp, lp);
}
