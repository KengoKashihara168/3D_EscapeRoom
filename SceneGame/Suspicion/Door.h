/*************************/
/* since:2018.01.07      */
/* file :Door.h          */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "Suspicion.h"

class Door : public Suspicion
{
public:
	// コンストラクタ
	Door();

	// 更新
	void Update(DirectX::SimpleMath::Vector3 playerPos);
	// 操作処理
	void Chackup();
};