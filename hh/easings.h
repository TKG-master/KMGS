#pragma once
#include <DirectXMath.h> // DirextXの数学関連のヘッダーファイル
#include <SimpleMath.h>

//イージング関数
//引数→（スタート地点・終了地点・時間の順番）
DirectX::SimpleMath::Vector3 EaseInOut(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaseInOutCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaseInOutQuart(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnSine(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnBack(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnOutBack(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnOutQuint(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnElastic(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnQuart(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaselnQutExpo(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaseInCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 EaseOutCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
DirectX::SimpleMath::Vector3 easeInOutElastic(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time);
