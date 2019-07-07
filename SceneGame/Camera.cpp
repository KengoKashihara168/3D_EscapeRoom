/*************************/
/* since:2018.12.07      */
/* file :camera.cpp      */
/* name :Kengo Kashihara */
/*************************/

#include "../pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Matrix Camera::m_view = Matrix();

// �萔�̏�����
const float Camera::DEFAULT_CAMERA_DISTANCE = 5.0f;
const float Camera::MODEL_HEIGHT = 15.0f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
	:m_eye(Vector3()),m_rotY(Matrix())
{

}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update()
{	
	// ���߂�ꂽ�����Ƀ^�[�Q�b�g��ݒ�
	Vector3 target = Vector3(0.0f, 0.0f, -DEFAULT_CAMERA_DISTANCE);

	// �v���C���[����擾������]�s������ƂɃ^�[�Q�b�g���ړ�
	target  = Vector3::Transform(target, m_rotY.Invert());

	// �^�[�Q�b�g�Ƀv���C���[�̍��W���ړ�
	target += m_eye;

	// �r���[�s��ɕϊ�
	m_view = Matrix::CreateLookAt(m_eye, target, Vector3::UnitY);
}


/// <summary>
/// ���_�̐ݒ�
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�s��</param>
void Camera::SetEyePosition(Vector3 pos,Matrix rot)
{
	// ���W
	m_eye = pos;
	// ����
	m_eye.y += MODEL_HEIGHT;
	// ����
	m_rotY = rot;
}
