/*************************/
/* since:2018.12.07      */
/* file :Sprites.cpp     */
/* name :Kengo Kashihara */
/*************************/
#include "pch.h"
#include "Sprites.h"

#include <codecvt>

#include "SingletonDR.h"

#include "SpriteBatch.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="name">画像の名前</param>
Sprites::Sprites(string name)
	:m_position(Vector2::Zero)// 座標の初期値
{
	// 文字列のコンバータ
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;

	std::wstring pass = L"Resources\\Textures\\" + cv.from_bytes(name) + L".png";
	// テクスチャのロード
	CreateWICTextureFromFile(SingletonDR::GetInstance().GetDevice(), pass.c_str(), nullptr, m_spriteData.GetAddressOf());
	int i = 0;
}

Sprites::~Sprites()
{
	m_spriteData.Reset();
}

/// <summary>
/// 描画
/// </summary>
void Sprites::Render()
{
	// スプライトの描画
	SingletonDR::GetInstance().GetSpriteBatch()->Begin(SpriteSortMode_Deferred, SingletonDR::GetInstance().GetCommonStates()->NonPremultiplied());
	SingletonDR::GetInstance().GetSpriteBatch()->Draw(m_spriteData.Get(), m_position);
	SingletonDR::GetInstance().GetSpriteBatch()->End();
}

/// <summary>
/// 座標の設定
/// </summary>
/// <param name="pos">座標</param>
void Sprites::SetPosition(Vector2 pos)
{
	m_position = pos;
}
