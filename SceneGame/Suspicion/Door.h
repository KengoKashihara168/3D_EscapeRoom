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
	// �R���X�g���N�^
	Door();

	// �X�V
	void Update(DirectX::SimpleMath::Vector3 playerPos);
	// ���쏈��
	void Chackup();
};