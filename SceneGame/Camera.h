/*************************/
/* since:2018.12.07      */
/* file :Camera.h        */
/* name :Kengo Kashihara */
/*************************/

#pragma once

class Camera
{
public:
	static const float DEFAULT_CAMERA_DISTANCE; // �J�����̋���

	static const float MODEL_HEIGHT;			// ���f���̍���

public:
	// �R���X�g���N�^
	Camera();

	// �X�V
	void Update();

	// �r���[�s��̎擾
	static DirectX::SimpleMath::Matrix GetView() { return m_view; }

	// ���_�̐ݒ�
	void SetEyePosition(DirectX::SimpleMath::Vector3 pos,DirectX::SimpleMath::Matrix rot);

private:

	
	static DirectX::SimpleMath::Matrix	m_view;					 // �������ꂽ�r���[�s��
	
	DirectX::SimpleMath::Vector3		m_eye;					 // ���_

	DirectX::SimpleMath::Matrix			m_rotY;					 // Y����]�s��
};
