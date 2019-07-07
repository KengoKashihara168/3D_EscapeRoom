/*************************/
/* since:2018.12.07      */
/* file :SceneTitle.cpp  */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "SceneTitle.h"
#include "../Sprites.h"

#include "../SingletonDR.h"

#include <codecvt>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle()
	:m_spin(0.0f)
{
	// タイトル画像
	m_title = new Sprites("title");
	// 「クリック」画像
	m_start = new Sprites("click");
}

/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Initialize()
{		
	/*ドア*/CreateObject("Door"			, 0, Vector3(-39, 0, 50), Vector3(0,  0, 0));
	/*前壁*/CreateObject("DoorSidePanel", 1, Vector3(  0, 0, 50), Vector3(0,  0, 0));
	/*後壁*/CreateObject("WallPanel"	, 2, Vector3(  0, 0,-50), Vector3(0,  0, 0));
	/*右壁*/CreateObject("WallPanel"	, 3, Vector3( 50, 0,  0), Vector3(0, 90, 0));
	/*左壁*/CreateObject("WallPanel"	, 4, Vector3(-50, 0,  0), Vector3(0, 90, 0));
	/*天井*/CreateObject("Ceiling"		, 5, Vector3(  0,29,  0), Vector3(0,  0, 0));

	// ビュー行列の設定
	m_view = Matrix::CreateLookAt(Vector3(0.0f, 70.0f, 180.0f), Vector3::Zero, Vector3::UnitY);
	// プロジェクション行列の設定
	SettingProjection();

	// タイトル画像の座標を設定
	m_title->SetPosition(Vector2(100, 100));
	// 「クリック」の座標を設定
	m_start->SetPosition(Vector2(300, 500));
}

/// <summary>
/// 更新
/// </summary>
void SceneTitle::Update()
{
	Mouse::State mouse = Mouse::Get().GetState();
	m_tracker.Update(mouse);
	// 左クリックされたら
	if (m_tracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// シーン切替用フラグをONにする
		m_changeFlag = true;
	}

	// 回転角度を進める
	m_spin += 0.5f;
}

/// <summary>
/// 描画
/// </summary>
void SceneTitle::Render()
{
	// モデルの描画
	for (int i = 0; i < 6; i++)
	{
		// 移動行列
		Matrix trans = Matrix::CreateTranslation(m_position[i]);
		// 回転行列(Y)
		Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(m_rotation[i].y));
		// 全体の回転行列
		Matrix spin = Matrix::CreateRotationY(XMConvertToRadians(m_spin));

		// ワールド行列の更新
		m_world = rotY * trans * spin;

		// モデルの描画
		m_model[i]->Draw(SingletonDR::GetInstance().GetContext(), *SingletonDR::GetInstance().GetCommonStates(), m_world, m_view, m_projection);
	}
	// タイトル画像の描画
	m_title->Render();
	// 「クリック」の描画
	m_start->Render();
}

/// <summary>
/// 終了
/// </summary>
void SceneTitle::Finalize()
{
	// スプライトの消去
	delete m_title;
	delete m_start;
}

/// <summary>
/// オブジェクトの生成
/// </summary>
/// <param name="name">	 モデルデータの名前	</param>
/// <param name="number">配列番号			</param>
/// <param name="pos">   座標				</param>
/// <param name="rot">   回転				</param>
void SceneTitle::CreateObject(std::string name, int number, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot)
{
	// モデルデータの読み込み
	LoadModel(name, number);
	// 座標の設定
	m_position[number] = pos;
	// 回転の設定
	m_rotation[number] = rot;
}

/// <summary>
/// ビュー行列の取得
/// </summary>
/// <returns>ビュー行列</returns>
Matrix SceneTitle::GetView()
{
	return m_view;
}

/// <summary>
/// モデルデータの読み込み
/// </summary>
/// <param name="name">	モデルデータの名前	</param>
/// <param name="num">	配列の番号			</param>
void SceneTitle::LoadModel(std::string name,int number)
{
	// エフェクトファクトリー
	DirectX::EffectFactory fx(SingletonDR::GetInstance().GetDevice());

	fx.SetDirectory(L"Resources\\Models");

	// 文字列のコンバータ
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;
	// モデルデータのパスを生成
	wstring pass = L"Resources\\Models\\" + cv.from_bytes(name) + L".cmo";

	// モデルデータの読み込み
	m_model[number] = Model::CreateFromCMO(SingletonDR::GetInstance().GetDevice(), pass.c_str(), fx);
}

/// <summary>
/// プロジェクション行列の設定
/// </summary>
void SceneTitle::SettingProjection()
{
	// ウインドウサイズからアスペクト比を算出する
	RECT size = SingletonDR::GetInstance().GetRectSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);
}