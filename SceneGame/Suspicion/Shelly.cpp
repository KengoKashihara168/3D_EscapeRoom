/*************************/
/* since:2018.01.07      */
/* file :Shelly.cpp      */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Shelly.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Shelly::Shelly()
{
	// 操作可能回数の設定
	m_chackCount = 1;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPos">親オブジェクトの座標</param>
void Shelly::Update(Vector3 playerPos)
{
	// マウス操作
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// 左クリックされたら
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// オブジェクトとプレイヤーの距離を求める
		Vector3 distance = CalculateDistance(m_position,m_parent->GetPosition()) - playerPos;
		float length = distance.Length();

		if (length < 30.0f) // 距離が30より小さければ
		{
			// 操作処理
			Chackup();
		}
	}	

	if (m_actionFlag == true && m_chackCount > 0) // 動作用フラグがtrueかつ操作可能回数が0より大きければ
	{
		if (EventFlag::GetInstance().GetEventFlag(EventFlag::SHELLY_TURNED) == false) // 人形の回転イベントが発生していなければ
		{
			// 回転処理
			Vector3 rot = m_targetRotation / (float)m_actionTime;
			m_rotation += rot;
			m_targetRotation -= rot;
			m_actionTime--;
		}		
	}

	if (m_actionTime == 0) // 動作時間が0になれば
	{
		m_actionFlag = false;
		EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::SHELLY_TURNED, true);
	}

	// 行列の更新
	UpdateMatrix();
}

/// <summary>
/// 操作処理
/// </summary>
void Shelly::Chackup()
{
	// 回転角度と時間の設定
	m_targetRotation.y = 180.0f;
	m_actionTime = 60;
	m_actionFlag = true;
}
