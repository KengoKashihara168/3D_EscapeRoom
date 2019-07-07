/*************************/
/* since:2018.12.07      */
/* file :Sprites.h       */
/* name :Kengo Kashihara */
/*************************/
#pragma once

class Sprites
{
public:
	// コンストラクタ
	Sprites(std::string name);
	// デストラクタ
	~Sprites();
	
	// 描画
	void Render();

	// 座標の設定
	void SetPosition(DirectX::SimpleMath::Vector2 pos);

	ID3D11ShaderResourceView* GetSpriteData() { return m_spriteData.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_spriteData;		// スプライトデータ
	DirectX::SimpleMath::Vector2						m_position;			// 座標
};
