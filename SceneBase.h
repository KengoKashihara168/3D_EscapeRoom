/*************************/
/* since:2018.12.07      */
/* file :SceneBase.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once

class SceneBase
{
public:
	// �V�[���̎��
	enum class SceneType
	{
		SceneNone,
		SceneTitle,
		SceneGame,
		SceneResult,
	};

public:
	// �R���X�g���N�^
	SceneBase();

	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;

	virtual void Finalize() = 0;

	// �V�[���ؑ֏��t���O�̎擾
	bool GetCnageFlag() { return m_changeFlag; }
	// �V�[���^�C�v�̎擾
	SceneType GetSceneType() { return m_sceneType; }
	// �V�[���^�C�v�̐ݒ�
	void SetSceneType(SceneType sceneType) { m_sceneType = sceneType; }

	// �r���[�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetView() = 0;

protected:
	bool		m_changeFlag; // �V�[���ؑ֗p�t���O

	SceneType	m_sceneType;  // �V�[���^�C�v
};