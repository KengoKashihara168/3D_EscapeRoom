/*************************/
/* since:2018.01.07      */
/* file :BigShelly.cpp   */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "BigShelly.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BigShelly::BigShelly()
{
	// 操作可能回数の設定
	m_chackCount = 1;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPos">親オブジェクトの座標</param>
void BigShelly::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// マウス操作
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// 左クリックされたら
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// プレイヤーとの距離を求める
		Vector3 distance = m_position - playerPos;
		float length = distance.Length();

		if (length < 30.0f)
		{
			// 操作処理
			Chackup();
		}
	}

	if (m_actionFlag == true && m_chackCount > 0)
	{
		if (EventFlag::GetInstance().GetEventFlag(EventFlag::BIGSHELLY_MOVED) == false) // 大人形のイベントが発生していなければ
		{
			// 移動処理
			Vector3 move = m_targetPosition / (float)m_actionTime;
			m_position += move;
			m_targetPosition -= move;
			m_actionTime--;
		}		
	}

	if (m_actionTime == 0)
	{
		m_actionFlag = false;
		EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::BIGSHELLY_MOVED, true);
	}

	// 行列の更新
	UpdateMatrix();
}

/// <summary>
/// 操作処理
/// </summary>
void BigShelly::Chackup()
{
	// 移動距離と時間の設定
	m_targetPosition.z = -30.0f;
	m_actionTime = 60;
	m_actionFlag = true;
}
