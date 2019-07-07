/*************************/
/* since:2018.12.07      */
/* file :SceneTitle.h    */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "../SceneBase.h"
#include <vector>

class Sprites;

class SceneTitle : public SceneBase
{
public:
	// コンストラクタ
	SceneTitle();

	// 初期化
	void Initialize()override;
	// 更新
	void Update()override;
	// 描画
	void Render()override;
	// 終了
	void Finalize()override;

	void CreateObject(std::string name, int number, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot);
	
	// ビュー行列の取得
	virtual DirectX::SimpleMath::Matrix GetView();

private:
	// モデルデータの読み込み
	void LoadModel(std::string name, int number);

	// プロジェクション行列の設定
	void SettingProjection();

private:
	std::unique_ptr<DirectX::Model>		m_model[6];			// モデルデータの配列

	DirectX::SimpleMath::Matrix			m_world;			// ワールド行列
	DirectX::SimpleMath::Matrix			m_view;				// ビュー行列
	DirectX::SimpleMath::Matrix			m_projection;		// プロジェクション行列

	DirectX::SimpleMath::Vector3		m_position[6];		// 各オブジェクトの座標
	DirectX::SimpleMath::Vector3		m_rotation[6];		// 各オブジェクトの角度
	float								m_spin;				// オブジェクトの回転角度(Y)

	DirectX::Mouse::ButtonStateTracker	m_tracker;			// マウストラッカー

	Sprites*							m_title;			// タイトル画像のスプライト
	Sprites*							m_start;			// 「クリック」のスプライト
};