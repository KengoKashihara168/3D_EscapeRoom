/*************************/
/* since:2018.12.07      */
/* file :camera.cpp      */
/* name :Kengo Kashihara */
/*************************/

#include "../pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Matrix Camera::m_view = Matrix();

// 定数の初期化
const float Camera::DEFAULT_CAMERA_DISTANCE = 5.0f;
const float Camera::MODEL_HEIGHT = 15.0f;


/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
	:m_eye(Vector3()),m_rotY(Matrix())
{

}

/// <summary>
/// 更新
/// </summary>
void Camera::Update()
{	
	// 決められた距離にターゲットを設定
	Vector3 target = Vector3(0.0f, 0.0f, -DEFAULT_CAMERA_DISTANCE);

	// プレイヤーから取得した回転行列をもとにターゲットを移動
	target  = Vector3::Transform(target, m_rotY.Invert());

	// ターゲットにプレイヤーの座標分移動
	target += m_eye;

	// ビュー行列に変換
	m_view = Matrix::CreateLookAt(m_eye, target, Vector3::UnitY);
}


/// <summary>
/// 視点の設定
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転行列</param>
void Camera::SetEyePosition(Vector3 pos,Matrix rot)
{
	// 座標
	m_eye = pos;
	// 高さ
	m_eye.y += MODEL_HEIGHT;
	// 向き
	m_rotY = rot;
}
