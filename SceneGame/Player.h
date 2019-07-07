/*************************/
/* since:2018.12.07      */
/* file :Player.h        */
/* name :Kengo Kashihara */
/*************************/

#pragma once

class Player
{
public:
	// コンストラクタ
	Player();

	// 初期化
	void Initialize();
	// 更新
	virtual void Update();

	// 移動
	void Move(DirectX::SimpleMath::Vector3 move);

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	// 向きの取得
	DirectX::SimpleMath::Matrix GetAngle() { return m_rotY; }

private:
	DirectX::SimpleMath::Vector3 m_position;		// 座標

	DirectX::SimpleMath::Matrix m_rotY;				// 向いている方向行列

	DirectX::Mouse::ButtonStateTracker m_tracker;	// マウストラッカー
};