/*************************/
/* since:2018.12.07      */
/* file :SceneGame.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include <map>
#include "../SceneBase.h"

// �N���X�̐錾
class Player;
class Camera;
class GameObject;
class Ornament;
class Suspicion;
class Item;

class SceneGame : public SceneBase
{
public:
	// �R���X�g���N�^
	SceneGame();

	// ������
	void Initialize()override;
	// �X�V
	void Update()override;
	// �`��
	void Render()override;
	// �I��
	void Finalize()override;

	// ����s�\�I�u�W�F�N�g�̐���
	void CreateOrnament(std::string name, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);
	void CreateOrnament(std::string key, std::string modelName, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);

	// �r���[�s��̍쐬
	DirectX::SimpleMath::Matrix GetView();

private:
	Player*								m_player;		// �v���C���[
	Camera*								m_camera;		// �J����

	std::map<std::string, Ornament*>	m_ornaments;	// ����s�\�I�u�W�F�N�g
	std::map<std::string, Suspicion*>	m_suspicions;	// ����\�I�u�W�F�N�g
	std::map<std::string, Item*>		m_items;		// �A�C�e��
};