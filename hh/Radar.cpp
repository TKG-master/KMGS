#include "Radar.h"
#include "Enemy.h"
#include <d3d11.h>

using namespace DirectX::SimpleMath;


void Radar::Init()
{
	// シェーダオブジェクト生成
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	// マテリアル生成
	MATERIAL	rmtrl;
	rmtrl.Ambient = Color(0, 0, 0, 0);
	rmtrl.Diffuse = Color(1, 1, 1, 1);
	rmtrl.Emission = Color(0, 0, 0, 0);
	rmtrl.Specular = Color(0, 0, 0, 0);
	rmtrl.Shiness = 0;
	rmtrl.TextureEnable = TRUE;

	m_Material.Create(rmtrl);

	m_Texture.Load("assets\\Texture\\siro.jpg");

}

void Radar::Update(DirectX::SimpleMath::Vector3 playerPosition, std::vector<Enemy*> enemies)
{

	playerpos = playerPosition;

	// プレイヤーの位置をレーダーの中心に設定
	m_RadarCenter = Vector2(playerPosition.x, playerPosition.z);

	// 敵の位置リストをクリアして更新
	m_EnemyPositions.clear();

	// レーダーの長方形のサイズ
	float radarWidth = 300.0f;
	float radarHeight = 250.0f;

	// スケーリングファクター（索敵範囲を広げるための係数）
	float scaleFactor = 3.0f;

	// スケーリング後の長方形のサイズ
	float scaledWidth = radarWidth * scaleFactor;
	float scaledHeight = radarHeight * scaleFactor;

	// 各敵の位置を処理
	for (int i = 0; i < enemies.size(); i++)
	{

		// プレイヤーから敵までの相対位置を計算
		Vector2 relativePos(enemies[i]->GetPosition().x - playerPosition.x, enemies[i]->GetPosition().z - playerPosition.z);

		// スケーリング後の範囲内に敵がいるかどうかを確認
		if (abs(relativePos.x) <= scaledWidth / 2 && abs(relativePos.y) <= scaledHeight / 2)
		{
			// 範囲内にいる場合、レーダーの位置に変換して保存
			Vector2 radarPos;
			radarPos.x = relativePos.x * (radarWidth / scaledWidth);
			radarPos.y = -relativePos.y * (radarHeight / scaledHeight); // Y座標の符号を反転
			enemies[i]->SetRaderPos(radarPos);
			//m_EnemyPositions.push_back(radarPos); // 敵の位置をリストに追加
			enemies[i]->SetRaderIn(true);
		}
		else
		{
			enemies[i]->SetRaderIn(false);
		}
	}

}

void Radar::Draw(const std::vector<Enemy*>& enemies)
{
	Renderer::SetWorldViewProjection2D();
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();

	m_Shader.SetGPU();
	m_Material.SetGPU();

	// レーダーの中心を設定
	Vector2 radarCenter = Vector2(1500, 150); // レーダーの画面上の位置
	//横幅と縦幅
	float width = 300.0f;
	float height = 250.0f;


	//長方形の４頂点の位置
	std::vector<VERTEX_3D> rectVertices(4);

	rectVertices[0].Position = Vector3(radarCenter.x - width / 2, radarCenter.y - height / 2, 0);
	rectVertices[1].Position = Vector3(radarCenter.x + width / 2, radarCenter.y - height / 2, 0);
	rectVertices[2].Position = Vector3(radarCenter.x - width / 2, radarCenter.y + height / 2, 0);
	rectVertices[3].Position = Vector3(radarCenter.x + width / 2, radarCenter.y + height / 2, 0);

	//長方形の色
	Color radarColor(0, 0.5, 0.5, 0.5f);
	for (int i = 0; i < 4; ++i)
	{
		rectVertices[i].Diffuse = radarColor;
	}

	//シェーダーにセット
	m_VertexBuffer.Create(rectVertices);
	m_VertexBuffer.SetGPU();
	m_Texture.SetGPU();
	
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->Draw(4, 0);

	// 各敵の位置を描画
	for (int i = 0; i < enemies.size(); ++i)
	{

		if (enemies[i]->GetRaderIn())
		{
			Vector2 enemyPos = radarCenter + enemies[i]->GetRaderPos();
			std::vector<VERTEX_3D> enemyVertices(4);

			float enemySize = 2.0f; // 敵の四角形のサイズ
			enemyVertices[0].Position = Vector3(enemyPos.x - enemySize, enemyPos.y - enemySize, 0);
			enemyVertices[1].Position = Vector3(enemyPos.x + enemySize, enemyPos.y - enemySize, 0);
			enemyVertices[2].Position = Vector3(enemyPos.x - enemySize, enemyPos.y + enemySize, 0);
			enemyVertices[3].Position = Vector3(enemyPos.x + enemySize, enemyPos.y + enemySize, 0);

			Color enemyColor(1, 0, 0, 1);
			for (int i = 0; i < 4; ++i)
			{
				enemyVertices[i].Diffuse = enemyColor;
			}

			m_VertexBuffer.Create(enemyVertices);
			m_VertexBuffer.SetGPU();

			devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			devicecontext->Draw(4, 0);


			float fanRadius = enemies[i]->Getlength() / 3.14f; // 扇型の半径（視野距離を縮小して表示）
			float viewAngle = enemies[i]->GetFov(); // 視野角
			Vector2 radarEnemyPosition = radarCenter + enemies[i]->GetRaderPos(); // レーダー上の敵の位置
			Vector2 forward = Vector2(enemies[i]->Getforward().x, enemies[i]->Getforward().z); // 敵の向いている方向

			forward.y = forward.y * -1;

			int numSegments = 20; // 扇型のセグメント数

			std::vector<VERTEX_3D> fanVertices(numSegments + 2); // 扇型の頂点数

			// 中心点の設定
			fanVertices[0].Position = Vector3(radarEnemyPosition.x, radarEnemyPosition.y, 0);
			Color fanColor(0.0f, 0.8f, 0.8f, 0.8f);
			fanVertices[0].Diffuse = fanColor;

			// 扇型のセグメントを計算
			for (int i = 0; i <= numSegments; ++i)
			{
				float angle = -viewAngle / 2 + viewAngle * i / numSegments;

				// forwardベクトルの方向に応じて角度を計算
				float radian = atan2(forward.y, forward.x);
				float x = radarEnemyPosition.x + cos(radian + angle) * fanRadius;
				float y = radarEnemyPosition.y + sin(radian + angle) * fanRadius;
				fanVertices[i + 1].Position = Vector3(x, y, 0);
				fanVertices[i + 1].Diffuse = fanColor;

			}

			// 扇型の頂点を三角形リストで描画するためのバッファを設定
			std::vector<VERTEX_3D> fanIndices;
			for (int i = 1; i < numSegments + 1; ++i)
			{
				fanIndices.push_back(fanVertices[0]);
				fanIndices.push_back(fanVertices[i]);
				fanIndices.push_back(fanVertices[i + 1]);
			}

			m_VertexBuffer.Create(fanIndices);
			m_VertexBuffer.SetGPU();

			// 扇型の描画用トポロジーを三角形リストに設定
			devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			devicecontext->Draw(fanIndices.size(), 0);
		}
	}

	// レーダーの中心に白い点を描画
	float pointSize = 2.0f; // 点のサイズ

	std::vector<VERTEX_3D> pointVertices(4); // 4 vertices for a small square representing the point

	// 点の頂点を設定
	pointVertices[0].Position = Vector3(radarCenter.x - pointSize / 2, radarCenter.y - pointSize / 2, 0);
	pointVertices[1].Position = Vector3(radarCenter.x + pointSize / 2, radarCenter.y - pointSize / 2, 0);
	pointVertices[2].Position = Vector3(radarCenter.x - pointSize / 2, radarCenter.y + pointSize / 2, 0);
	pointVertices[3].Position = Vector3(radarCenter.x + pointSize / 2, radarCenter.y + pointSize / 2, 0);

	Color pointColor(1, 1, 1, 1); // 白色
	for (int i = 0; i < 4; ++i)
	{
		pointVertices[i].Diffuse = pointColor;
	}

	// 点用の頂点バッファを設定
	m_VertexBuffer.Create(pointVertices);
	m_VertexBuffer.SetGPU();

	// トポロジーを三角形ストリップに設定
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->Draw(4, 0);
}


void Radar::Dispose()
{

}
