/*************************/
/* since:2018.01.07      */
/* file :Suspicion.cpp   */
/* name :Kengo Kashihara */
/*************************/
#include "../../pch.h"
#include "Suspicion.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Suspicion::Suspicion()
	:m_targetPosition(Vector3())
	,m_targetRotation(Vector3())
	,m_actionTime(-1)
	,m_chackCount(0)
	,m_actionFlag(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Suspicion::~Suspicion()
{

}

