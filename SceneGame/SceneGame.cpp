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
/// コンストラクタ
/// </summary>
SceneGame::SceneGame()
{
	m_player = new Player(); // プレイヤー
	m_camera = new Camera(); // カメラ
}

/// <summary>
/// 初期化
/// </summary>
void SceneGame::Initialize()
{
	// プレイヤーの初期化
	m_player->Initialize();

	// オブジェクトの生成
	/* 床      */CreateOrnament("Floor", Vector3::Zero, Vector3::Zero);
	/* 天井    */CreateOrnament("Ceiling", Vector3(0, 30, 0), Vector3::Zero);
	/* 壁(右)  */CreateOrnament("WallEast", "WallPanel", Vector3(50, 0, 0), Vector3(0, 90, 0));
	/* 壁(左)  */CreateOrnament("WallWest", "DoorSidePanel", Vector3(-50, 0, 0), Vector3(0, 90, 0));
	/* 壁(手前)*/CreateOrnament("WallSouth", "WallPanel", Vector3(0, 0, 50), Vector3(0, 0, 0));
	/* 壁(奥)  */CreateOrnament("WallNorth", "WallPanel", Vector3(0, 0, -50), Vector3(0, 0, 0));
	/* 棚      */CreateOrnament("Stack", Vector3(30, 0, -47), Vector3::Zero);

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
/// 更新
/// </summary>
void SceneGame::Update()
{
	// プレイヤーの更新
	m_player->Update();

	// カメラの更新
	m_camera->SetEyePosition(m_player->GetPosition(),m_player->GetAngle());
	m_camera->Update();

	

	// 操作可能オブジェクトの更新
	for (map<string, Suspicion*>::iterator ite = m_suspicions.begin(); ite != m_suspicions.end(); ite++)
	{
		pair<string, Suspicion*> suspicionPair = *ite;		
		suspicionPair.second->Update(m_player->GetPosition());
		suspicionPair.second->UpdateMatrix();
	}

	// アイテムの更新
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
/// 描画
/// </summary>
void SceneGame::Render()
{
	// 操作不能オブジェクトの描画
	for (map<string, Ornament*>::iterator ite = m_ornaments.begin(); ite != m_ornaments.end(); ite++)
	{
		pair<string, Ornament*> ornamentPair = *ite;
		ornamentPair.second->Render();
	}

	// 操作可能オブジェクトの描画
	for (map<string, Suspicion*>::iterator ite = m_suspicions.begin(); ite != m_suspicions.end(); ite++)
	{
		pair<string, Suspicion*> suspicionPair = *ite;		
		suspicionPair.second->Render();
	}

	// 鍵の描画
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
/// 終了
/// </summary>
void SceneGame::Finalize()
{
	delete m_player; // プレイヤーの消去
	delete m_camera; // カメラの消去

	// 操作不能オブジェクトの消去
	for (map<string, Ornament*>::iterator ite = m_ornaments.begin(); ite != m_ornaments.end(); ite++)
	{
		pair<string, Ornament*> ornamentPair = *ite;
		delete ornamentPair.second;
	}
	m_ornaments.clear();

	// 操作可能オブジェクトの消去
	for (map<string, Suspicion*>::iterator ite = m_suspicions.begin(); ite != m_suspicions.end(); ite++)
	{
		pair<string, Suspicion*> suspicionPair = *ite;
		delete suspicionPair.second;
	}
	m_suspicions.clear();

	// アイテムの消去	
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
/// 操作不能オブジェクトの生成
/// </summary>
/// <param name="name">		キー(モデルデータ)の名前</param>
/// <param name="pos">		座標					</param>
/// <param name="rot">		回転角					</param>
/// <param name="parent">	親の行列ポインタ		</param>
void SceneGame::CreateOrnament(string name, Vector3 pos, Vector3 rot, GameObject* parent)
{
	m_ornaments[name] = new Ornament();
	m_ornaments[name]->Initialize(name, pos, rot, parent);
}

/// <summary>
/// 操作不能オブジェクトの生成
/// </summary>
/// <param name="key">		キーの名前			</param>
/// <param name="modelName">モデルデータの名前	</param>
/// <param name="pos">		座標				</param>
/// <param name="rot">		回転角				</param>
/// <param name="parent">	親の行列ポインタ	</param>
void SceneGame::CreateOrnament(string name,string modelName, Vector3 pos, Vector3 rot, GameObject* parent)
{
	m_ornaments[name] = new Ornament();
	m_ornaments[name]->Initialize(modelName, pos, rot, parent);
}

/// <summary>
/// ビュー行列の取得
/// </summary>
/// <returns>カメラのビュー行列</returns>
Matrix SceneGame::GetView()
{
	return m_camera->GetView();
}

