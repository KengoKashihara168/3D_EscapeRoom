/*************************/
/* since:2018.12.07      */
/* file :Camera.h        */
/* name :Kengo Kashihara */
/*************************/

#pragma once

class Camera
{
public:
	static const float DEFAULT_CAMERA_DISTANCE; // カメラの距離

	static const float MODEL_HEIGHT;			// モデルの高さ

public:
	// コンストラクタ
	Camera();

	// 更新
	void Update();

	// ビュー行列の取得
	static DirectX::SimpleMath::Matrix GetView() { return m_view; }

	// 視点の設定
	void SetEyePosition(DirectX::SimpleMath::Vector3 pos,DirectX::SimpleMath::Matrix rot);

private:

	
	static DirectX::SimpleMath::Matrix	m_view;					 // 生成されたビュー行列
	
	DirectX::SimpleMath::Vector3		m_eye;					 // 視点

	DirectX::SimpleMath::Matrix			m_rotY;					 // Y軸回転行列
};
