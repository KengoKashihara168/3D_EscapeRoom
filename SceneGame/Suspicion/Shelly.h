/*************************/
/* since:2018.01.07      */
/* file :Shelly.h        */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "Suspicion.h"

class Shelly : public Suspicion
{
public:
	// コンストラクタ
	Shelly();

	// 更新
	void Update(DirectX::SimpleMath::Vector3 playerPos);
	// 操作処理
	void Chackup();
};