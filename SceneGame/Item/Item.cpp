/*************************/
/* since:2018.12.07      */
/* file :Item.cpp        */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Item.h"
#include "../../Sprites.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Item::Item()
	:m_spriteFlag(false)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Item::~Item()
{
	delete m_sprite; // �X�v���C�g�̍폜
}

/// <summary>
/// ������
/// </summary>
/// <param name="name">�I�u�W�F�N�g��</param>
void Item::Initialize(std::string name, Vector3 pos, Vector3 rot, GameObject* parent)
{
	GameObject::Initialize(name, pos, rot, parent);

	// �X�v���C�g�̎��̉�
	m_sprite = new Sprites(name);
}

/// <summary>
/// �`��
/// </summary>
void Item::Render()
{
	if (m_spriteFlag == false) // �X�v���C�g���`�悳��Ȃ��Ȃ�
	{
		// ���N���X�̕`��֐��Ăяo��
		GameObject::Render();
	}
	else
	{
		// �X�v���C�g�̕`��
		m_sprite->Render();
	}
}

/// <summary>
/// ���쏈��
/// </summary>
void Item::Checkup()
{
	if (m_spriteFlag == true) // �X�v���C�g���`�悳���Ȃ�
	{
		// �������Ȃ�
		return;
	}
	else
	{
		// �X�v���C�g��`�悷��
		m_spriteFlag = true;
	}
}