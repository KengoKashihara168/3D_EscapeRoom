/*************************/
/* since:2018.12.07      */
/* file :GameObject.cpp  */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "GameObject.h"
#include "Camera.h"

#include <codecvt>

#include "../SingletonDR.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
GameObject::GameObject()
	:m_parent(nullptr), m_position(Vector3()), m_rotation(Vector3()), m_world(Matrix())
{
	
}

GameObject::~GameObject()
{
	m_model.reset();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="name">モデルの名前</param>
void GameObject::Initialize(const string name, Vector3 pos, Vector3 rot, GameObject* parent)
{
	LoadModel(name);

	m_position = pos;
	m_rotation = rot;

	m_parent = parent;

	UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void GameObject::Render()
{
	if (m_model != nullptr)
	{
		// モデルの描画
		m_model->Draw(SingletonDR::GetInstance().GetContext(), *SingletonDR::GetInstance().GetCommonStates(), m_world, Camera::GetView(), GetProjection());
	}	
}

/// <summary>
/// モデルデータの読み込み
/// </summary>
/// <param name="name">モデルの名前</param>
void GameObject::LoadModel(const string name)
{
	// エフェクトファクトリー
	DirectX::EffectFactory fx(SingletonDR::GetInstance().GetDevice());

	fx.SetDirectory(L"Resources\\Models");

	// 文字列のコンバータ
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;
	// モデルデータのパスを生成
	wstring pass = L"Resources\\Models\\" + cv.from_bytes(name) + L".cmo";

	// モデルデータの読み込み
	m_model = Model::CreateFromCMO(SingletonDR::GetInstance().GetDevice(), pass.c_str(), fx);
}

/// <summary>
/// 行列の更新
/// </summary>
void GameObject::UpdateMatrix()
{
	// 描画用行列
	Matrix trans = Matrix::CreateTranslation(m_position);						// 座標行列の設定
	Matrix rotX  = Matrix::CreateRotationX(XMConvertToRadians(m_rotation.x));	// X軸回転行列の設定
	Matrix rotY  = Matrix::CreateRotationY(XMConvertToRadians(m_rotation.y));	// Y軸回転行列の設定
	Matrix rotZ  = Matrix::CreateRotationZ(XMConvertToRadians(m_rotation.z));	// Z軸回転行列の設定

	m_world = rotX * rotY * rotZ * trans;

	if (m_parent != nullptr)
	{
		m_world *= m_parent->GetWorld();
	}
}

/// <summary>
/// プロジェクション行列の取得
/// </summary>
/// <returns>プロジェクション行列</returns>
Matrix GameObject::GetProjection()
{
	// ウインドウサイズからアスペクト比を算出する
	RECT size = SingletonDR::GetInstance().GetRectSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f, // ニアクリップ
		200.0f // ファークリップ
	);

	return projection;
}

Vector3 GameObject::CalculateDistance(Vector3 base, Vector3 subPos)
{
	Vector3 distance = base;

	if (m_parent->m_parent != nullptr)
	{
		distance = m_parent->CalculateDistance(m_parent->GetPosition(),m_parent->m_parent->GetPosition());
	}

	distance += subPos;

	return distance;
}
