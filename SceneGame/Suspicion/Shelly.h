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
	// �R���X�g���N�^
	Shelly();

	// �X�V
	void Update(DirectX::SimpleMath::Vector3 playerPos);
	// ���쏈��
	void Chackup();
};