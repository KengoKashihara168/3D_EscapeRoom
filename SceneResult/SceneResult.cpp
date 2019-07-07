/*************************/
/* since:2018.12.07      */
/* file :SceneResult.cpp */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "SceneResult.h"
#include "../Sprites.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneResult::SceneResult()
{
	m_result = new Sprites("result");		// �N���A�摜�̃X�v���C�g
	m_logo   = new Sprites("MyLogo_200");	// ���S�}�[�N�̃X�v���C�g
}

/// <summary>
/// ������
/// </summary>
void SceneResult::Initialize()
{
	// �V�[���ؑ֗p�J�E���^�̏�����
	m_count = 0;
	// �N���A�摜�̍��W��ݒ�
	m_result->SetPosition(Vector2(0, 0));
	// ���S�}�[�N�̍��W��ݒ�
	m_logo->SetPosition(Vector2(600, 400));
}

/// <summary>
/// �X�V
/// </summary>
void SceneResult::Update()
{
	// �J�E���^��i�߂�
	m_count++;

	if (m_count >= 240) // 240�t���[���𒴂�����
	{
		// �V�[���ؑ֗p�t���O��ON�ɂ���
		m_changeFlag = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void SceneResult::Render()
{
	// �N���A�摜�̕`��
	m_result->Render();
	// ���S�}�[�N�̕`��
	m_logo->Render();
}

/// <summary>
/// �I��
/// </summary>
void SceneResult::Finalize()
{
	delete m_result;	// �N���A�摜�̃X�v���C�g������
	delete m_logo;		// ���S�}�[�N�̏���
}

/// <summary>
/// �r���[�s��̎擾
/// </summary>
/// <returns>�s��</returns>
DirectX::SimpleMath::Matrix SceneResult::GetView()
{
	return DirectX::SimpleMath::Matrix();
}
