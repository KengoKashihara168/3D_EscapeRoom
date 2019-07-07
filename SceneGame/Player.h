/*************************/
/* since:2018.12.07      */
/* file :Player.h        */
/* name :Kengo Kashihara */
/*************************/

#pragma once

class Player
{
public:
	// �R���X�g���N�^
	Player();

	// ������
	void Initialize();
	// �X�V
	virtual void Update();

	// �ړ�
	void Move(DirectX::SimpleMath::Vector3 move);

	// ���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	// �����̎擾
	DirectX::SimpleMath::Matrix GetAngle() { return m_rotY; }

private:
	DirectX::SimpleMath::Vector3 m_position;		// ���W

	DirectX::SimpleMath::Matrix m_rotY;				// �����Ă�������s��

	DirectX::Mouse::ButtonStateTracker m_tracker;	// �}�E�X�g���b�J�[
};