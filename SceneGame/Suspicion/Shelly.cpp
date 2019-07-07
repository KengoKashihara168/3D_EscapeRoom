/*************************/
/* since:2018.01.07      */
/* file :Shelly.cpp      */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Shelly.h"
#include "../EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shelly::Shelly()
{
	// ����\�񐔂̐ݒ�
	m_chackCount = 1;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPos">�e�I�u�W�F�N�g�̍��W</param>
void Shelly::Update(Vector3 playerPos)
{
	// �}�E�X����
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);

	// ���N���b�N���ꂽ��
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// �I�u�W�F�N�g�ƃv���C���[�̋��������߂�
		Vector3 distance = CalculateDistance(m_position,m_parent->GetPosition()) - playerPos;
		float length = distance.Length();

		if (length < 30.0f) // ������30��菬�������
		{
			// ���쏈��
			Chackup();
		}
	}	

	if (m_actionFlag == true && m_chackCount > 0) // ����p�t���O��true������\�񐔂�0���傫�����
	{
		if (EventFlag::GetInstance().GetEventFlag(EventFlag::SHELLY_TURNED) == false) // �l�`�̉�]�C�x���g���������Ă��Ȃ����
		{
			// ��]����
			Vector3 rot = m_targetRotation / (float)m_actionTime;
			m_rotation += rot;
			m_targetRotation -= rot;
			m_actionTime--;
		}		
	}

	if (m_actionTime == 0) // ���쎞�Ԃ�0�ɂȂ��
	{
		m_actionFlag = false;
		EventFlag::GetInstance().SetEventFlag(EventFlag::EVENT_KIND::SHELLY_TURNED, true);
	}

	// �s��̍X�V
	UpdateMatrix();
}

/// <summary>
/// ���쏈��
/// </summary>
void Shelly::Chackup()
{
	// ��]�p�x�Ǝ��Ԃ̐ݒ�
	m_targetRotation.y = 180.0f;
	m_actionTime = 60;
	m_actionFlag = true;
}
