/*************************/
/* since:2018.01.07      */
/* file :BigShelly.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "Suspicion.h"

class BigShelly : public Suspicion
{
public:
	// コンストラクタ
	BigShelly();

	// 更新
	void Update(DirectX::SimpleMath::Vector3 playerPos);
	// 操作処理
	void Chackup();
};