/*************************/
/* since:2018.01.07      */
/* file :EventFlag.h     */
/* name :Kengo Kashihara */
/*************************/
#pragma once

class EventFlag
{
public:
	enum EVENT_KIND
	{
		SHELLY_TURNED,	// �l�`�̉�]
		KEY_GETTING,	// ���̎擾
		BIGSHELLY_MOVED,// ��l�`�̈ړ�
		DOOR_OPEN,		// �h�A���J����

		EVENT_TOTAL		// �C�x���g�̑���
	};

private:
	// �R���X�g���N�^
	EventFlag();

	void operator=(const EventFlag& obj) {}

	EventFlag(const EventFlag &obj) {}
public:
	static EventFlag& GetInstance();

	// �C�x���g�t���O�̐ݒ�
	void SetEventFlag(EVENT_KIND kind,bool flag);
	// �C�x���g�t���O�̎擾
	bool GetEventFlag(EVENT_KIND kind);

	void Reset();

private:
	bool m_eventFlag[EVENT_KIND::EVENT_TOTAL]; // �C�x���g�t���O�p�z��
};