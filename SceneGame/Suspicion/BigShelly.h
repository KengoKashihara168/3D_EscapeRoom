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
	// �R���X�g���N�^
	BigShelly();

	// �X�V
	void Update(DirectX::SimpleMath::Vector3 playerPos);
	// ���쏈��
	void Chackup();
};