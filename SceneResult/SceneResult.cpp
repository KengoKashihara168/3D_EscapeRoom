/*************************/
/* since:2018.12.07      */
/* file :SceneResult.cpp */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "SceneResult.h"
#include "../Sprites.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
SceneResult::SceneResult()
{
	m_result = new Sprites("result");		// クリア画像のスプライト
	m_logo   = new Sprites("MyLogo_200");	// ロゴマークのスプライト
}

/// <summary>
/// 初期化
/// </summary>
void SceneResult::Initialize()
{
	// シーン切替用カウンタの初期化
	m_count = 0;
	// クリア画像の座標を設定
	m_result->SetPosition(Vector2(0, 0));
	// ロゴマークの座標を設定
	m_logo->SetPosition(Vector2(600, 400));
}

/// <summary>
/// 更新
/// </summary>
void SceneResult::Update()
{
	// カウンタを進める
	m_count++;

	if (m_count >= 240) // 240フレームを超えたら
	{
		// シーン切替用フラグをONにする
		m_changeFlag = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void SceneResult::Render()
{
	// クリア画像の描画
	m_result->Render();
	// ロゴマークの描画
	m_logo->Render();
}

/// <summary>
/// 終了
/// </summary>
void SceneResult::Finalize()
{
	delete m_result;	// クリア画像のスプライトを消去
	delete m_logo;		// ロゴマークの消去
}

/// <summary>
/// ビュー行列の取得
/// </summary>
/// <returns>行列</returns>
DirectX::SimpleMath::Matrix SceneResult::GetView()
{
	return DirectX::SimpleMath::Matrix();
}
