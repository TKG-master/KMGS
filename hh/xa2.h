//=============================================================================
//
// サウンド処理 [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>
#include <vector>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_TEST = 0,

	SOUND_LABEL_TITLEBGM,
	SOUND_LABEL_STAGE1_BGM,
	SOUND_LABEL_STAGE2_BGM,
	SOUND_LABEL_STAGE3_BGM,

	SOUND_LABEL_FADEIN,
	SOUND_LABEL_FADEOUT,
	SOUND_LABEL_BOOKSE,
	SOUND_LABEL_GAMEOVER,
	SOUND_LABEL_GAMEOVER_2,
	SOUND_LABEL_DAMAGEHIT,
	SOUND_LABEL_FLY,
	SOUND_LABEL_CURSOR,
	SOUND_LABEL_GAMECLEAR,
	SOUND_LABEL_GAMECLEAR2,
	SOUND_LABEL_PRESS,

	SOUND_LABEL_FALL,
	SOUND_LABEL_GETUP,
	SOUND_LABEL_JUMP,
	SOUND_LABEL_BREAK,
	SOUND_LABEL_DOWN,

	SOUND_LABEL_SCORE_COUNT,
	SOUND_LABEL_CLEAR,
	SOUND_LABEL_KURAKKA,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
} PARAM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

// ゲームループ開始前に呼び出すサウンドの初期化処理
HRESULT XA_Initialize(void);

// ゲームループ終了後に呼び出すサウンドの解放処理
void XA_Release(void);

// 引数で指定したサウンドを再生する
void XA_Play(SOUND_LABEL label);

// 引数で指定したサウンドを停止する
void XA_Stop(SOUND_LABEL label);

// 引数で指定したサウンドの再生を再開する
void XA_Resume(SOUND_LABEL label);

#endif
