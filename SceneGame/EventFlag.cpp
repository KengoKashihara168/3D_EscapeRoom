/*************************/
/* since:2018.01.07      */
/* file :EventFlag.cpp   */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "EventFlag.h"

/// <summary>
/// コンストラクタ
/// </summary>
EventFlag::EventFlag()
{
	Reset();
}

EventFlag& EventFlag::GetInstance()
{
	static EventFlag instance;

	return instance;
}

/// <summary>
/// イベントフラグの設定
/// </summary>
/// <param name="kind">イベントの種類</param>
/// <param name="flag">設定するフラグ</param>
void EventFlag::SetEventFlag(EVENT_KIND kind, bool flag)
{
	m_eventFlag[kind] = flag;
}

/// <summary>
/// イベントフラグの取得
/// </summary>
/// <param name="kind">イベントの種類</param>
/// <returns>イベントのフラグ</returns>
bool EventFlag::GetEventFlag(EVENT_KIND kind)
{
	return m_eventFlag[kind];
}

/// <summary>
/// イベントの初期化
/// </summary>
void EventFlag::Reset()
{
	for (int i = 0; i < EVENT_KIND::EVENT_TOTAL; i++)
	{
		m_eventFlag[i] = false;
	}
}
