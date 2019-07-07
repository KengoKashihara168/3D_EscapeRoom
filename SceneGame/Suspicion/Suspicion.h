/*************************/
/* since:2018.01.07      */
/* file :Suspicion.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "../GameObject.h"

class Suspicion :public GameObject
{
public:
	// コンストラクタ
	Suspicion();
	// デストラクタ
	~Suspicion();

	// 更新
	virtual void Update(DirectX::SimpleMath::Vector3 playerPos) {};
	// 操作処理
	virtual void Chackup() {};

protected:
	DirectX::SimpleMath::Vector3 m_targetPosition;
	DirectX::SimpleMath::Vector3 m_targetRotation;

	int m_actionTime;

	int m_chackCount;
	bool m_actionFlag;

	DirectX::Mouse::ButtonStateTracker	m_tracker;		// マウストラッカー
};
