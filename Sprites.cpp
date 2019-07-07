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
/// �R���X�g���N�^
/// </summary>
/// <param name="name">�摜�̖��O</param>
Sprites::Sprites(string name)
	:m_position(Vector2::Zero)// ���W�̏����l
{
	// ������̃R���o�[�^
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;

	std::wstring pass = L"Resources\\Textures\\" + cv.from_bytes(name) + L".png";
	// �e�N�X�`���̃��[�h
	CreateWICTextureFromFile(SingletonDR::GetInstance().GetDevice(), pass.c_str(), nullptr, m_spriteData.GetAddressOf());
	int i = 0;
}

Sprites::~Sprites()
{
	m_spriteData.Reset();
}

/// <summary>
/// �`��
/// </summary>
void Sprites::Render()
{
	// �X�v���C�g�̕`��
	SingletonDR::GetInstance().GetSpriteBatch()->Begin(SpriteSortMode_Deferred, SingletonDR::GetInstance().GetCommonStates()->NonPremultiplied());
	SingletonDR::GetInstance().GetSpriteBatch()->Draw(m_spriteData.Get(), m_position);
	SingletonDR::GetInstance().GetSpriteBatch()->End();
}

/// <summary>
/// ���W�̐ݒ�
/// </summary>
/// <param name="pos">���W</param>
void Sprites::SetPosition(Vector2 pos)
{
	m_position = pos;
}
