/*************************/
/* since:2018.12.07      */
/* file :Player.cpp      */
/* name :Kengo Kashihara */
/*************************/

#include "../pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	:m_position(Vector3()),m_rotY(Matrix::Identity)
{
	
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	m_position = Vector3(0.0f, 0.0f, 35.0f);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// キーボードのシングルトン
	Keyboard::State kb = Keyboard::Get().GetState();
	
	// プレイヤーの移動速度
	Vector3 moveDirection = Vector3::Zero;
	
	if (kb.A || kb.Left) // 「A」が押されたら
	{
		m_rotY *= Matrix::CreateRotationY(XMConvertToRadians(-1));
	}
	if (kb.D || kb.Right) // 「D」が押されたら
	{
		m_rotY *= Matrix::CreateRotationY(XMConvertToRadians(1));
	}

	if (kb.W || kb.Up) // 「W」が押されたら
	{
		moveDirection.z = -1.0f; // 前進
	}
	if (kb.S || kb.Down) // 「S」が押されたら
	{
		moveDirection.z = 1.0f;  // 後進
	}
	
	// 移動させる
	Move(moveDirection);	
}

/// <summary>
/// 移動
/// </summary>
/// <param name="move">移動速度</param>
void Player::Move(DirectX::SimpleMath::Vector3 move)
{
	// 座標の更新
	m_position += Vector3::Transform(move, m_rotY.Invert());

	// プレイヤーの移動先が部屋の外なら移動しない
	if (m_position.x >= 35.0f)  { m_position.x -= 1.0f; } // 右
	if (m_position.x <= -35.0f) { m_position.x += 1.0f; } // 左
	if (m_position.z >= 35.0f)  { m_position.z -= 1.0f; } // 後
	if (m_position.z <= -35.0f) { m_position.z += 1.0f; } // 前
}