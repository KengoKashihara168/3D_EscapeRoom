/*************************/
/* since:2018.12.07      */
/* file :Player.cpp      */
/* name :Kengo Kashihara */
/*************************/

#include "../pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:m_position(Vector3()),m_rotY(Matrix::Identity)
{
	
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
	m_position = Vector3(0.0f, 0.0f, 35.0f);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update()
{
	// �L�[�{�[�h�̃V���O���g��
	Keyboard::State kb = Keyboard::Get().GetState();
	
	// �v���C���[�̈ړ����x
	Vector3 moveDirection = Vector3::Zero;
	
	if (kb.A || kb.Left) // �uA�v�������ꂽ��
	{
		m_rotY *= Matrix::CreateRotationY(XMConvertToRadians(-1));
	}
	if (kb.D || kb.Right) // �uD�v�������ꂽ��
	{
		m_rotY *= Matrix::CreateRotationY(XMConvertToRadians(1));
	}

	if (kb.W || kb.Up) // �uW�v�������ꂽ��
	{
		moveDirection.z = -1.0f; // �O�i
	}
	if (kb.S || kb.Down) // �uS�v�������ꂽ��
	{
		moveDirection.z = 1.0f;  // ��i
	}
	
	// �ړ�������
	Move(moveDirection);	
}

/// <summary>
/// �ړ�
/// </summary>
/// <param name="move">�ړ����x</param>
void Player::Move(DirectX::SimpleMath::Vector3 move)
{
	// ���W�̍X�V
	m_position += Vector3::Transform(move, m_rotY.Invert());

	// �v���C���[�̈ړ��悪�����̊O�Ȃ�ړ����Ȃ�
	if (m_position.x >= 35.0f)  { m_position.x -= 1.0f; } // �E
	if (m_position.x <= -35.0f) { m_position.x += 1.0f; } // ��
	if (m_position.z >= 35.0f)  { m_position.z -= 1.0f; } // ��
	if (m_position.z <= -35.0f) { m_position.z += 1.0f; } // �O
}