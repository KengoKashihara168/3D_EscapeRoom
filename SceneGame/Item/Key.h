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
	// �R���X�g���N�^
	Key();

	// �X�V
	void Update(DirectX::SimpleMath::Vector3 playerPos)override;
	// �`��
	void Render()override;
};
