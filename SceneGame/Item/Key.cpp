/*************************/
/* since:2018.12.21      */
/* file :Key.cpp         */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Key.h"
#include "../../Sprites.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Key::Key()
{
	
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPos">親オブジェクトの座標</param>
void Key::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// マウスの取得
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// 左クリックされたら
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// プレイヤーとの距離を求める
		Vector3 distance = CalculateDistance(m_position, m_parent->GetPosition()) - playerPos;
		float length = distance.Length();

		if (length < 30.0f &&
			EventFlag::GetInstance().GetEventFlag(EventFlag::EVENT_KIND::SHELLY_TURNED) == true && // 人形が回転している
			EventFlag::GetInstance().GetEventFlag(EventFlag::EVENT_KIND::KEY_GETTING)   == false)  // 鍵のイベントが発生していなければ
		{
			// 操作処理
			Checkup();
			EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::KEY_GETTING, true);
		}
	}

	if (m_spriteFlag == true) // 画像を表示するなら
	{
		Vector2 mousePos = Vector2((float)(mouse.x - 50), (float)(mouse.y - 50)); // マウス座標
		m_sprite->SetPosition(mousePos);										  // マウス座標をスプライト座標に設定
	}

	if (EventFlag::GetInstance().GetEventFlag(EventFlag::DOOR_OPEN)) // ドアが開いたら
	{
		// 画像の描画をやめる
		m_spriteFlag = false;
	}

	// 行列の更新
	UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Key::Render()
{
	if (EventFlag::GetInstance().GetEventFlag(EventFlag::KEY_GETTING) == false) // 鍵が取得されていなければ
	{
		// 3Dモデルの描画
		GameObject::Render();
	}
	else
	{
		if (m_spriteFlag == true) // 画像が描画されるなら
		{
			// スプライトの描画
			m_sprite->Render();
		}		
	}
}
