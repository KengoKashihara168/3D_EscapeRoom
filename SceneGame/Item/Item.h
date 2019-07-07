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
	// �R���X�g���N�^
	Item();
	// �f�X�g���N�^
	~Item();

	// �I�u�W�F�N�g�̐���
	//static Item* Create(std::string key);

	// ������
	void Initialize(const std::string name, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);

	// �X�V
	virtual void Update(DirectX::SimpleMath::Vector3 playerPos) {};

	// �`��
	virtual void Render();

	// ���쏈��
	virtual void Checkup();

	// �X�v���C�g�`��p�t���O�̎擾
	bool GetSpriteFlag() { return m_spriteFlag; }

protected:
	Sprites* m_sprite;									// �X�v���C�g
	bool m_spriteFlag;									// �X�v���C�g�`��p�t���O

	DirectX::Mouse::ButtonStateTracker	m_tracker;		// �}�E�X�g���b�J�[
};
