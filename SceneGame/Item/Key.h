/*************************/
/* since:2018.12.21      */
/* file :Key.h           */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "Item.h"

class Key : public Item
{
public:
	// コンストラクタ
	Key();

	// 更新
	void Update(DirectX::SimpleMath::Vector3 playerPos)override;
	// 描画
	void Render()override;
};
