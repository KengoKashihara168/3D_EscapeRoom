/*************************/
/* since:2018.01.07      */
/* file :BigShelly.cpp   */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "BigShelly.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BigShelly::BigShelly()
{
	// ����\�񐔂̐ݒ�
	m_chackCount = 1;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPos">�e�I�u�W�F�N�g�̍��W</param>
void BigShelly::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// �}�E�X����
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// ���N���b�N���ꂽ��
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// �v���C���[�Ƃ̋��������߂�
		Vector3 distance = m_position - playerPos;
		float length = distance.Length();

		if (length < 30.0f)
		{
			// ���쏈��
			Chackup();
		}
	}

	if (m_actionFlag == true && m_chackCount > 0)
	{
		if (EventFlag::GetInstance().GetEventFlag(EventFlag::BIGSHELLY_MOVED) == false) // ��l�`�̃C�x���g���������Ă��Ȃ����
		{
			// �ړ�����
			Vector3 move = m_targetPosition / (float)m_actionTime;
			m_position += move;
			m_targetPosition -= move;
			m_actionTime--;
		}		
	}

	if (m_actionTime == 0)
	{
		m_actionFlag = false;
		EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::BIGSHELLY_MOVED, true);
	}

	// �s��̍X�V
	UpdateMatrix();
}

/// <summary>
/// ���쏈��
/// </summary>
void BigShelly::Chackup()
{
	// �ړ������Ǝ��Ԃ̐ݒ�
	m_targetPosition.z = -30.0f;
	m_actionTime = 60;
	m_actionFlag = true;
}
