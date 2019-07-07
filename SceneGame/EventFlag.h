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
		SHELLY_TURNED,	// 人形の回転
		KEY_GETTING,	// 鍵の取得
		BIGSHELLY_MOVED,// 大人形の移動
		DOOR_OPEN,		// ドアを開ける

		EVENT_TOTAL		// イベントの総数
	};

private:
	// コンストラクタ
	EventFlag();

	void operator=(const EventFlag& obj) {}

	EventFlag(const EventFlag &obj) {}
public:
	static EventFlag& GetInstance();

	// イベントフラグの設定
	void SetEventFlag(EVENT_KIND kind,bool flag);
	// イベントフラグの取得
	bool GetEventFlag(EVENT_KIND kind);

	void Reset();

private:
	bool m_eventFlag[EVENT_KIND::EVENT_TOTAL]; // イベントフラグ用配列
};