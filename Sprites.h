/*************************/
/* since:2018.12.07      */
/* file :Sprites.h       */
/* name :Kengo Kashihara */
/*************************/
#pragma once

class Sprites
{
public:
	// �R���X�g���N�^
	Sprites(std::string name);
	// �f�X�g���N�^
	~Sprites();
	
	// �`��
	void Render();

	// ���W�̐ݒ�
	void SetPosition(DirectX::SimpleMath::Vector2 pos);

	ID3D11ShaderResourceView* GetSpriteData() { return m_spriteData.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_spriteData;		// �X�v���C�g�f�[�^
	DirectX::SimpleMath::Vector2						m_position;			// ���W
};
