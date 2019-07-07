/*************************/
/* since:2018.01.07      */
/* file :EventFlag.cpp   */
/* name :Kengo Kashihara */
/*************************/
#include "../pch.h"
#include "EventFlag.h"

/// <summary>
/// �R���X�g���N�^
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
/// �C�x���g�t���O�̐ݒ�
/// </summary>
/// <param name="kind">�C�x���g�̎��</param>
/// <param name="flag">�ݒ肷��t���O</param>
void EventFlag::SetEventFlag(EVENT_KIND kind, bool flag)
{
	m_eventFlag[kind] = flag;
}

/// <summary>
/// �C�x���g�t���O�̎擾
/// </summary>
/// <param name="kind">�C�x���g�̎��</param>
/// <returns>�C�x���g�̃t���O</returns>
bool EventFlag::GetEventFlag(EVENT_KIND kind)
{
	return m_eventFlag[kind];
}

/// <summary>
/// �C�x���g�̏�����
/// </summary>
void EventFlag::Reset()
{
	for (int i = 0; i < EVENT_KIND::EVENT_TOTAL; i++)
	{
		m_eventFlag[i] = false;
	}
}
