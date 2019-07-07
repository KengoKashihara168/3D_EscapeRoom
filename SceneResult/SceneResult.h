/*************************/
/* since:2018.12.07      */
/* file :SceneResult.h   */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "../SceneBase.h"

class Sprites;

class SceneResult :public SceneBase
{
public:
	// コンストラクタ
	SceneResult();

	// 初期化
	void Initialize()override;
	// 更新
	void Update()override;
	// 描画
	void Render()override;
	// 終了
	void Finalize()override;

	// ビュー行列の取得
	virtual DirectX::SimpleMath::Matrix GetView();

private:
	int m_count; // シーン切替用カウンタ

	Sprites* m_result;	// クリア画像のスプライト
	Sprites* m_logo;	// ロゴマークのスプライト
};