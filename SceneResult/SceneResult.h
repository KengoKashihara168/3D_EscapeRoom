/*************************/
/* since:2018.12.07      */
/* file :SceneResult.h   */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "../SceneBase.h"

class Sprites;

class SceneResult :public SceneBase
{
public:
	// �R���X�g���N�^
	SceneResult();

	// ������
	void Initialize()override;
	// �X�V
	void Update()override;
	// �`��
	void Render()override;
	// �I��
	void Finalize()override;

	// �r���[�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetView();

private:
	int m_count; // �V�[���ؑ֗p�J�E���^

	Sprites* m_result;	// �N���A�摜�̃X�v���C�g
	Sprites* m_logo;	// ���S�}�[�N�̃X�v���C�g
};