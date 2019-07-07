/*************************/
/* since:2018.12.07      */
/* file :Item.cpp        */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Item.h"
#include "../../Sprites.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Item::Item()
	:m_spriteFlag(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Item::~Item()
{
	delete m_sprite; // スプライトの削除
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="name">オブジェクト名</param>
void Item::Initialize(std::string name, Vector3 pos, Vector3 rot, GameObject* parent)
{
	GameObject::Initialize(name, pos, rot, parent);

	// スプライトの実体化
	m_sprite = new Sprites(name);
}

/// <summary>
/// 描画
/// </summary>
void Item::Render()
{
	if (m_spriteFlag == false) // スプライトが描画されないなら
	{
		// 基底クラスの描画関数呼び出し
		GameObject::Render();
	}
	else
	{
		// スプライトの描画
		m_sprite->Render();
	}
}

/// <summary>
/// 操作処理
/// </summary>
void Item::Checkup()
{
	if (m_spriteFlag == true) // スプライトが描画されるなら
	{
		// 何もしない
		return;
	}
	else
	{
		// スプライトを描画する
		m_spriteFlag = true;
	}
}