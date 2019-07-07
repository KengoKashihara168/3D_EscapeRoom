/*************************/
/* since:2018.12.07      */
/* file :GameObject.h    */
/* name :Kengo Kashihara */
/*************************/
#pragma once

#include <Model.h>

class GameObject
{
public:
	// �R���X�g���N�^
	GameObject();

	// �f�X�g���N�^
	~GameObject();
public:
	// ������
	virtual void Initialize(const std::string name, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);

	// �`��
	virtual void Render();

	// �s��̍X�V
	void UpdateMatrix();

	// ���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	// ��]�p�̎擾
	DirectX::SimpleMath::Vector3 GetRotation() { return m_rotation; }
	// ���[���h�s��̎擾
	DirectX::SimpleMath::Matrix  GetWorld() { return m_world; }

	DirectX::SimpleMath::Vector3 CalculateDistance(DirectX::SimpleMath::Vector3 base, DirectX::SimpleMath::Vector3 subPos);

protected:
	// ���f���f�[�^�̓ǂݍ���
	void LoadModel(const std::string name);

private:
	// �v���W�F�N�V�����s��̎擾
	DirectX::SimpleMath::Matrix GetProjection();

protected:
	std::unique_ptr<DirectX::Model> m_model;			// ���f���n���h��
	DirectX::SimpleMath::Vector3    m_position;			// ���W
	DirectX::SimpleMath::Vector3    m_rotation;			// ��]�p�x

	DirectX::SimpleMath::Matrix		m_world;			// ���[���h�s��

	GameObject* m_parent;
};

