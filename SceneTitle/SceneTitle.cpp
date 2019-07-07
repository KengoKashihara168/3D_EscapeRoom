/*************************/
/* since:2018.12.07      */
/* file :SceneTitle.cpp  */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "SceneTitle.h"
#include "../Sprites.h"

#include "../SingletonDR.h"

#include <codecvt>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle()
	:m_spin(0.0f)
{
	// �^�C�g���摜
	m_title = new Sprites("title");
	// �u�N���b�N�v�摜
	m_start = new Sprites("click");
}

/// <summary>
/// ������
/// </summary>
void SceneTitle::Initialize()
{		
	/*�h�A*/CreateObject("Door"			, 0, Vector3(-39, 0, 50), Vector3(0,  0, 0));
	/*�O��*/CreateObject("DoorSidePanel", 1, Vector3(  0, 0, 50), Vector3(0,  0, 0));
	/*���*/CreateObject("WallPanel"	, 2, Vector3(  0, 0,-50), Vector3(0,  0, 0));
	/*�E��*/CreateObject("WallPanel"	, 3, Vector3( 50, 0,  0), Vector3(0, 90, 0));
	/*����*/CreateObject("WallPanel"	, 4, Vector3(-50, 0,  0), Vector3(0, 90, 0));
	/*�V��*/CreateObject("Ceiling"		, 5, Vector3(  0,29,  0), Vector3(0,  0, 0));

	// �r���[�s��̐ݒ�
	m_view = Matrix::CreateLookAt(Vector3(0.0f, 70.0f, 180.0f), Vector3::Zero, Vector3::UnitY);
	// �v���W�F�N�V�����s��̐ݒ�
	SettingProjection();

	// �^�C�g���摜�̍��W��ݒ�
	m_title->SetPosition(Vector2(100, 100));
	// �u�N���b�N�v�̍��W��ݒ�
	m_start->SetPosition(Vector2(300, 500));
}

/// <summary>
/// �X�V
/// </summary>
void SceneTitle::Update()
{
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);
	// ���N���b�N���ꂽ��
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// �V�[���ؑ֗p�t���O��ON�ɂ���
		m_changeFlag = true;
	}

	// ��]�p�x��i�߂�
	m_spin += 0.5f;
}

/// <summary>
/// �`��
/// </summary>
void SceneTitle::Render()
{
	// ���f���̕`��
	for (int i = 0; i < 6; i++)
	{
		// �ړ��s��
		Matrix trans = Matrix::CreateTranslation(m_position[i]);
		// ��]�s��(Y)
		Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(m_rotation[i].y));
		// �S�̂̉�]�s��
		Matrix spin = Matrix::CreateRotationY(XMConvertToRadians(m_spin));

		// ���[���h�s��̍X�V
		m_world = rotY * trans * spin;

		// ���f���̕`��
		m_model[i]->Draw(SingletonDR::GetInstance().GetContext(), *SingletonDR::GetInstance().GetCommonStates(), m_world, m_view, m_projection);
	}
	// �^�C�g���摜�̕`��
	m_title->Render();
	// �u�N���b�N�v�̕`��
	m_start->Render();
}

/// <summary>
/// �I��
/// </summary>
void SceneTitle::Finalize()
{
	// �X�v���C�g�̏���
	delete m_title;
	delete m_start;
}

/// <summary>
/// �I�u�W�F�N�g�̐���
/// </summary>
/// <param name="name">	 ���f���f�[�^�̖��O	</param>
/// <param name="number">�z��ԍ�			</param>
/// <param name="pos">   ���W				</param>
/// <param name="rot">   ��]				</param>
void SceneTitle::CreateObject(std::string name, int number, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot)
{
	// ���f���f�[�^�̓ǂݍ���
	LoadModel(name, number);
	// ���W�̐ݒ�
	m_position[number] = pos;
	// ��]�̐ݒ�
	m_rotation[number] = rot;
}

/// <summary>
/// �r���[�s��̎擾
/// </summary>
/// <returns>�r���[�s��</returns>
Matrix SceneTitle::GetView()
{
	return m_view;
}

/// <summary>
/// ���f���f�[�^�̓ǂݍ���
/// </summary>
/// <param name="name">	���f���f�[�^�̖��O	</param>
/// <param name="num">	�z��̔ԍ�			</param>
void SceneTitle::LoadModel(std::string name,int number)
{
	// �G�t�F�N�g�t�@�N�g���[
	DirectX::EffectFactory fx(SingletonDR::GetInstance().GetDevice());

	fx.SetDirectory(L"Resources\\Models");

	// ������̃R���o�[�^
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;
	// ���f���f�[�^�̃p�X�𐶐�
	wstring pass = L"Resources\\Models\\" + cv.from_bytes(name) + L".cmo";

	// ���f���f�[�^�̓ǂݍ���
	m_model[number] = Model::CreateFromCMO(SingletonDR::GetInstance().GetDevice(), pass.c_str(), fx);
}

/// <summary>
/// �v���W�F�N�V�����s��̐ݒ�
/// </summary>
void SceneTitle::SettingProjection()
{
	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = SingletonDR::GetInstance().GetRectSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);

	// �ˉe�s����쐬����
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);
}