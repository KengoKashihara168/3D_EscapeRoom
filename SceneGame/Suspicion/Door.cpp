/*************************/
/* since:2018.01.07      */
/* file :Door.cpp        */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Door.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Door::Door()
{
	// 操作可能回数の設定
	m_chackCount = 1;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPos">親オブジェクトの座標</param>
void Door::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// マウス操作
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// 左クリックされたら
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// オブジェクトとプレイヤーの距離を求める
		Vector3 distance = m_position - playerPos;
		float length = distance.Length();

		if (length < 25.0f)
		{
			// 操作処理
			Chackup();
		}
	}

	if (m_actionFlag == true && m_chackCount > 0)
	{
		if (EventFlag::GetInstance().GetEventFlag(EventFlag::DOOR_OPEN) == false &&    // ドアが開いていない
			EventFlag::GetInstance().GetEventFlag(EventFlag::KEY_GETTING) == true &&   // 鍵を取得している
			EventFlag::GetInstance().GetEventFlag(EventFlag::BIGSHELLY_MOVED) == true) // 大きな人形が移動している
		{
			// 回転処理
			Vector3 rot = m_targetRotation / (float)m_actionTime;
			m_rotation += rot;
			m_targetRotation -= rot;
			m_actionTime--;
		}
	}	

	if (m_actionTime == 0)
	{
		m_actionFlag = false;
		EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::DOOR_OPEN, true);
	}

	// 行列の更新
	UpdateMatrix();
}

/// <summary>
/// 操作処理
/// </summary>
void Door::Chackup()
{
	// 回転角度と時間の設定
	m_targetRotation.y = 90.0f;
	m_actionTime = 60;
	m_actionFlag = true;
}
