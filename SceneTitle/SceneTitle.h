/*************************/
/* since:2018.12.07      */
/* file :SceneTitle.h    */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "../SceneBase.h"
#include <vector>

class Sprites;

class SceneTitle : public SceneBase
{
public:
	// �R���X�g���N�^
	SceneTitle();

	// ������
	void Initialize()override;
	// �X�V
	void Update()override;
	// �`��
	void Render()override;
	// �I��
	void Finalize()override;

	void CreateObject(std::string name, int number, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot);
	
	// �r���[�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetView();

private:
	// ���f���f�[�^�̓ǂݍ���
	void LoadModel(std::string name, int number);

	// �v���W�F�N�V�����s��̐ݒ�
	void SettingProjection();

private:
	std::unique_ptr<DirectX::Model>		m_model[6];			// ���f���f�[�^�̔z��

	DirectX::SimpleMath::Matrix			m_world;			// ���[���h�s��
	DirectX::SimpleMath::Matrix			m_view;				// �r���[�s��
	DirectX::SimpleMath::Matrix			m_projection;		// �v���W�F�N�V�����s��

	DirectX::SimpleMath::Vector3		m_position[6];		// �e�I�u�W�F�N�g�̍��W
	DirectX::SimpleMath::Vector3		m_rotation[6];		// �e�I�u�W�F�N�g�̊p�x
	float								m_spin;				// �I�u�W�F�N�g�̉�]�p�x(Y)

	DirectX::Mouse::ButtonStateTracker	m_tracker;			// �}�E�X�g���b�J�[

	Sprites*							m_title;			// �^�C�g���摜�̃X�v���C�g
	Sprites*							m_start;			// �u�N���b�N�v�̃X�v���C�g
};