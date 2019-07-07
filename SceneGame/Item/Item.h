/*************************/
/* since:2018.12.07      */
/* file :Item.h          */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "../GameObject.h"

class Sprites;

class Item :public GameObject
{
public:
	// コンストラクタ
	Item();
	// デストラクタ
	~Item();

	// オブジェクトの生成
	//static Item* Create(std::string key);

	// 初期化
	void Initialize(const std::string name, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);

	// 更新
	virtual void Update(DirectX::SimpleMath::Vector3 playerPos) {};

	// 描画
	virtual void Render();

	// 操作処理
	virtual void Checkup();

	// スプライト描画用フラグの取得
	bool GetSpriteFlag() { return m_spriteFlag; }

protected:
	Sprites* m_sprite;									// スプライト
	bool m_spriteFlag;									// スプライト描画用フラグ

	DirectX::Mouse::ButtonStateTracker	m_tracker;		// マウストラッカー
};
