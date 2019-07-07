/*************************/
/* since:2018.12.07      */
/* file :SceneBase.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once

class SceneBase
{
public:
	// シーンの種類
	enum class SceneType
	{
		SceneNone,
		SceneTitle,
		SceneGame,
		SceneResult,
	};

public:
	// コンストラクタ
	SceneBase();

	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;

	virtual void Finalize() = 0;

	// シーン切替小フラグの取得
	bool GetCnageFlag() { return m_changeFlag; }
	// シーンタイプの取得
	SceneType GetSceneType() { return m_sceneType; }
	// シーンタイプの設定
	void SetSceneType(SceneType sceneType) { m_sceneType = sceneType; }

	// ビュー行列の取得
	virtual DirectX::SimpleMath::Matrix GetView() = 0;

protected:
	bool		m_changeFlag; // シーン切替用フラグ

	SceneType	m_sceneType;  // シーンタイプ
};