/*************************/
/* since:2018.12.07      */
/* file :GameObject.cpp  */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "GameObject.h"
#include "Camera.h"

#include <codecvt>

#include "../SingletonDR.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObject::GameObject()
	:m_parent(nullptr), m_position(Vector3()), m_rotation(Vector3()), m_world(Matrix())
{
	
}

GameObject::~GameObject()
{
	m_model.reset();
}

/// <summary>
/// ������
/// </summary>
/// <param name="name">���f���̖��O</param>
void GameObject::Initialize(const string name, Vector3 pos, Vector3 rot, GameObject* parent)
{
	LoadModel(name);

	m_position = pos;
	m_rotation = rot;

	m_parent = parent;

	UpdateMatrix();
}

/// <summary>
/// �`��
/// </summary>
void GameObject::Render()
{
	if (m_model != nullptr)
	{
		// ���f���̕`��
		m_model->Draw(SingletonDR::GetInstance().GetContext(), *SingletonDR::GetInstance().GetCommonStates(), m_world, Camera::GetView(), GetProjection());
	}	
}

/// <summary>
/// ���f���f�[�^�̓ǂݍ���
/// </summary>
/// <param name="name">���f���̖��O</param>
void GameObject::LoadModel(const string name)
{
	// �G�t�F�N�g�t�@�N�g���[
	DirectX::EffectFactory fx(SingletonDR::GetInstance().GetDevice());

	fx.SetDirectory(L"Resources\\Models");

	// ������̃R���o�[�^
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;
	// ���f���f�[�^�̃p�X�𐶐�
	wstring pass = L"Resources\\Models\\" + cv.from_bytes(name) + L".cmo";

	// ���f���f�[�^�̓ǂݍ���
	m_model = Model::CreateFromCMO(SingletonDR::GetInstance().GetDevice(), pass.c_str(), fx);
}

/// <summary>
/// �s��̍X�V
/// </summary>
void GameObject::UpdateMatrix()
{
	// �`��p�s��
	Matrix trans = Matrix::CreateTranslation(m_position);						// ���W�s��̐ݒ�
	Matrix rotX  = Matrix::CreateRotationX(XMConvertToRadians(m_rotation.x));	// X����]�s��̐ݒ�
	Matrix rotY  = Matrix::CreateRotationY(XMConvertToRadians(m_rotation.y));	// Y����]�s��̐ݒ�
	Matrix rotZ  = Matrix::CreateRotationZ(XMConvertToRadians(m_rotation.z));	// Z����]�s��̐ݒ�

	m_world = rotX * rotY * rotZ * trans;

	if (m_parent != nullptr)
	{
		m_world *= m_parent->GetWorld();
	}
}

/// <summary>
/// �v���W�F�N�V�����s��̎擾
/// </summary>
/// <returns>�v���W�F�N�V�����s��</returns>
Matrix GameObject::GetProjection()
{
	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = SingletonDR::GetInstance().GetRectSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);

	// �ˉe�s����쐬����
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f, // �j�A�N���b�v
		200.0f // �t�@�[�N���b�v
	);

	return projection;
}

Vector3 GameObject::CalculateDistance(Vector3 base, Vector3 subPos)
{
	Vector3 distance = base;

	if (m_parent->m_parent != nullptr)
	{
		distance = m_parent->CalculateDistance(m_parent->GetPosition(),m_parent->m_parent->GetPosition());
	}

	distance += subPos;

	return distance;
}
