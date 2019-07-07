/*************************/
/* since:2018.12.07      */
/* file :GameObject.h    */
/* name :Kengo Kashihara */
/*************************/
#pragma once

#include <Model.h>

class GameObject
{
public:
	// コンストラクタ
	GameObject();

	// デストラクタ
	~GameObject();
public:
	// 初期化
	virtual void Initialize(const std::string name, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);

	// 描画
	virtual void Render();

	// 行列の更新
	void UpdateMatrix();

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	// 回転角の取得
	DirectX::SimpleMath::Vector3 GetRotation() { return m_rotation; }
	// ワールド行列の取得
	DirectX::SimpleMath::Matrix  GetWorld() { return m_world; }

	DirectX::SimpleMath::Vector3 CalculateDistance(DirectX::SimpleMath::Vector3 base, DirectX::SimpleMath::Vector3 subPos);

protected:
	// モデルデータの読み込み
	void LoadModel(const std::string name);

private:
	// プロジェクション行列の取得
	DirectX::SimpleMath::Matrix GetProjection();

protected:
	std::unique_ptr<DirectX::Model> m_model;			// モデルハンドル
	DirectX::SimpleMath::Vector3    m_position;			// 座標
	DirectX::SimpleMath::Vector3    m_rotation;			// 回転角度

	DirectX::SimpleMath::Matrix		m_world;			// ワールド行列

	GameObject* m_parent;
};

