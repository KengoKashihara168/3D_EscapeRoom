/*************************/
/* since:2018.01.07      */
/* file :Door.cpp        */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Door.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Door::Door()
{
	// ����\�񐔂̐ݒ�
	m_chackCount = 1;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPos">�e�I�u�W�F�N�g�̍��W</param>
void Door::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// �}�E�X����
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// ���N���b�N���ꂽ��
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// �I�u�W�F�N�g�ƃv���C���[�̋��������߂�
		Vector3 distance = m_position - playerPos;
		float length = distance.Length();

		if (length < 25.0f)
		{
			// ���쏈��
			Chackup();
		}
	}

	if (m_actionFlag == true && m_chackCount > 0)
	{
		if (EventFlag::GetInstance().GetEventFlag(EventFlag::DOOR_OPEN) == false &&    // �h�A���J���Ă��Ȃ�
			EventFlag::GetInstance().GetEventFlag(EventFlag::KEY_GETTING) == true &&   // �����擾���Ă���
			EventFlag::GetInstance().GetEventFlag(EventFlag::BIGSHELLY_MOVED) == true) // �傫�Ȑl�`���ړ����Ă���
		{
			// ��]����
			Vector3 rot = m_targetRotation / (float)m_actionTime;
			m_rotation += rot;
			m_targetRotation -= rot;
			m_actionTime--;
		}
	}	

	if (m_actionTime == 0)
	{
		m_actionFlag = false;
		EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::DOOR_OPEN, true);
	}

	// �s��̍X�V
	UpdateMatrix();
}

/// <summary>
/// ���쏈��
/// </summary>
void Door::Chackup()
{
	// ��]�p�x�Ǝ��Ԃ̐ݒ�
	m_targetRotation.y = 90.0f;
	m_actionTime = 60;
	m_actionFlag = true;
}
