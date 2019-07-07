/*************************/
/* since:2018.12.21      */
/* file :Key.cpp         */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Key.h"
#include "../../Sprites.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Key::Key()
{
	
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPos">�e�I�u�W�F�N�g�̍��W</param>
void Key::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// �}�E�X�̎擾
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// ���N���b�N���ꂽ��
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// �v���C���[�Ƃ̋��������߂�
		Vector3 distance = CalculateDistance(m_position, m_parent->GetPosition()) - playerPos;
		float length = distance.Length();

		if (length < 30.0f &&
			EventFlag::GetInstance().GetEventFlag(EventFlag::EVENT_KIND::SHELLY_TURNED) == true && // �l�`����]���Ă���
			EventFlag::GetInstance().GetEventFlag(EventFlag::EVENT_KIND::KEY_GETTING)   == false)  // ���̃C�x���g���������Ă��Ȃ����
		{
			// ���쏈��
			Checkup();
			EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::KEY_GETTING, true);
		}
	}

	if (m_spriteFlag == true) // �摜��\������Ȃ�
	{
		Vector2 mousePos = Vector2((float)(mouse.x - 50), (float)(mouse.y - 50)); // �}�E�X���W
		m_sprite->SetPosition(mousePos);										  // �}�E�X���W���X�v���C�g���W�ɐݒ�
	}

	if (EventFlag::GetInstance().GetEventFlag(EventFlag::DOOR_OPEN)) // �h�A���J������
	{
		// �摜�̕`�����߂�
		m_spriteFlag = false;
	}

	// �s��̍X�V
	UpdateMatrix();
}

/// <summary>
/// �`��
/// </summary>
void Key::Render()
{
	if (EventFlag::GetInstance().GetEventFlag(EventFlag::KEY_GETTING) == false) // �����擾����Ă��Ȃ����
	{
		// 3D���f���̕`��
		GameObject::Render();
	}
	else
	{
		if (m_spriteFlag == true) // �摜���`�悳���Ȃ�
		{
			// �X�v���C�g�̕`��
			m_sprite->Render();
		}		
	}
}
