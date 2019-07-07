/*************************/
/* since:2018.12.07      */
/* file :SceneGame.cpp   */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include"Ornament\Ornament.h"
#include "Suspicion\Shelly.h"
#include "Suspicion\BigShelly.h"
#include "Suspicion\Door.h"
#include "Item\Key.h"
#include "EventFlag.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneGame::SceneGame()
{
	m_player = new Player(); // �v���C���[
	m_camera = new Camera(); // �J����
}

/// <summary>
/// ������
/// </summary>
void SceneGame::Initialize()
{
	// �v���C���[�̏�����
	m_player->Initialize();

	// �I�u�W�F�N�g�̐���
	/* ��      */CreateOrnament("Floor", Vector3::Zero, Vector3::Zero);
	/* �V��    */CreateOrnament("Ceiling", Vector3(0, 30, 0), Vector3::Zero);
	/* ��(�E)  */CreateOrnament("WallEast", "WallPanel", Vector3(50, 0, 0), Vector3(0, 90, 0));
	/* ��(��)  */CreateOrnament("WallWest", "DoorSidePanel", Vector3(-50, 0, 0), Vector3(0, 90, 0));
	/* ��(��O)*/CreateOrnament("WallSouth", "WallPanel", Vector3(0, 0, 50), Vector3(0, 0, 0));
	/* ��(��)  */CreateOrnament("WallNorth", "WallPanel", Vector3(0, 0, -50), Vector3(0, 0, 0));
	/* �I      */CreateOrnament("Stack", Vector3(30, 0, -47), Vector3::Zero);

	m_suspicions["Shelly"] = new Shelly();
	m_suspicions["Shelly"]->Initialize("Shelly", Vector3(0, 10, 0), Vector3::Zero, m_ornaments["Stack"]);

	m_suspicions["BigShelly"] = new BigShelly();
	m_suspicions["BigShelly"]->Initialize("BigShelly", Vector3(-40.0f, 0.0f, 30.0f), Vector3(0.0f, 90.0f, 0.0f));

	m_suspicions["Door"] = new Door();
	m_suspicions["Door"]->Initialize("Door", Vector3(-39, 0, 0), Vector3::Zero, m_ornaments["WallWest"]);

	m_items["Key"] = new Key();
	m_items["Key"]->Initialize("Key", Vector3(0.0f, 0.0f, -0.7f), Vector3(-10.0f,180.0f,0.0f), m_suspicions["Shelly"]);
}

/// <summary>
/// �X�V
/// </summary>
void SceneGame::Update()
{
	// �v���C���[�̍X�V
	m_player->Update();

	// �J�����̍X�V
	m_camera->SetEyePosition(m_player->GetPosition(),m_player->GetAngle());
	m_camera->Update();

	

	// ����\�I�u�W�F�N�g�̍X�V
	for (map<string, Suspicion*>::iterator ite = m_suspicions.begin(); ite != m_suspicions.end(); ite++)
	{
		pair<string, Suspicion*> suspicionPair = *ite;		
		suspicionPair.second->Update(m_player->GetPosition());
		suspicionPair.second->UpdateMatrix();
	}

	// �A�C�e���̍X�V
	for (map<string, Item*>::iterator ite = m_items.begin(); ite != m_items.end(); ite++)
	{
		pair<string, Item*> itemPair = *ite;			
		if (itemPair.second)
		{
			itemPair.second->Update(m_player->GetPosition());
			itemPair.second->UpdateMatrix();
		}
	}

	if (EventFlag::GetInstance().GetEventFlag(EventFlag::DOOR_OPEN) == true)
	{
		m_changeFlag = true;
		EventFlag::GetInstance().Reset();
	}
}

/// <summary>
/// �`��
/// </summary>
void SceneGame::Render()
{
	// ����s�\�I�u�W�F�N�g�̕`��
	for (map<string, Ornament*>::iterator ite = m_ornaments.begin(); ite != m_ornaments.end(); ite++)
	{
		pair<string, Ornament*> ornamentPair = *ite;
		ornamentPair.second->Render();
	}

	// ����\�I�u�W�F�N�g�̕`��
	for (map<string, Suspicion*>::iterator ite = m_suspicions.begin(); ite != m_suspicions.end(); ite++)
	{
		pair<string, Suspicion*> suspicionPair = *ite;		
		suspicionPair.second->Render();
	}

	// ���̕`��
	for (map<string, Item*>::iterator ite = m_items.begin(); ite != m_items.end(); ite++)
	{
		pair<string, Item*> itemPair = *ite;
		if (itemPair.second)
		{
			itemPair.second->Render();
		}
	}
}

/// <summary>
/// �I��
/// </summary>
void SceneGame::Finalize()
{
	delete m_player; // �v���C���[�̏���
	delete m_camera; // �J�����̏���

	// ����s�\�I�u�W�F�N�g�̏���
	for (map<string, Ornament*>::iterator ite = m_ornaments.begin(); ite != m_ornaments.end(); ite++)
	{
		pair<string, Ornament*> ornamentPair = *ite;
		delete ornamentPair.second;
	}
	m_ornaments.clear();

	// ����\�I�u�W�F�N�g�̏���
	for (map<string, Suspicion*>::iterator ite = m_suspicions.begin(); ite != m_suspicions.end(); ite++)
	{
		pair<string, Suspicion*> suspicionPair = *ite;
		delete suspicionPair.second;
	}
	m_suspicions.clear();

	// �A�C�e���̏���	
	for (map<string, Item*>::iterator ite = m_items.begin(); ite != m_items.end(); ite++)
	{
		pair<string, Item*> itemPair = *ite;
		if (itemPair.second)
		{
			delete itemPair.second;
		}
	}
	m_items.clear();
}

/// <summary>
/// ����s�\�I�u�W�F�N�g�̐���
/// </summary>
/// <param name="name">		�L�[(���f���f�[�^)�̖��O</param>
/// <param name="pos">		���W					</param>
/// <param name="rot">		��]�p					</param>
/// <param name="parent">	�e�̍s��|�C���^		</param>
void SceneGame::CreateOrnament(string name, Vector3 pos, Vector3 rot, GameObject* parent)
{
	m_ornaments[name] = new Ornament();
	m_ornaments[name]->Initialize(name, pos, rot, parent);
}

/// <summary>
/// ����s�\�I�u�W�F�N�g�̐���
/// </summary>
/// <param name="key">		�L�[�̖��O			</param>
/// <param name="modelName">���f���f�[�^�̖��O	</param>
/// <param name="pos">		���W				</param>
/// <param name="rot">		��]�p				</param>
/// <param name="parent">	�e�̍s��|�C���^	</param>
void SceneGame::CreateOrnament(string name,string modelName, Vector3 pos, Vector3 rot, GameObject* parent)
{
	m_ornaments[name] = new Ornament();
	m_ornaments[name]->Initialize(modelName, pos, rot, parent);
}

/// <summary>
/// �r���[�s��̎擾
/// </summary>
/// <returns>�J�����̃r���[�s��</returns>
Matrix SceneGame::GetView()
{
	return m_camera->GetView();
}

