/*************************/
/* since:2018.12.07      */
/* file :SceneGame.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include <map>
#include "../SceneBase.h"

// クラスの宣言
class Player;
class Camera;
class GameObject;
class Ornament;
class Suspicion;
class Item;

class SceneGame : public SceneBase
{
public:
	// コンストラクタ
	SceneGame();

	// 初期化
	void Initialize()override;
	// 更新
	void Update()override;
	// 描画
	void Render()override;
	// 終了
	void Finalize()override;

	// 操作不能オブジェクトの生成
	void CreateOrnament(std::string name, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);
	void CreateOrnament(std::string key, std::string modelName, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, GameObject* parent = nullptr);

	// ビュー行列の作成
	DirectX::SimpleMath::Matrix GetView();

private:
	Player*								m_player;		// プレイヤー
	Camera*								m_camera;		// カメラ

	std::map<std::string, Ornament*>	m_ornaments;	// 操作不能オブジェクト
	std::map<std::string, Suspicion*>	m_suspicions;	// 操作可能オブジェクト
	std::map<std::string, Item*>		m_items;		// アイテム
};