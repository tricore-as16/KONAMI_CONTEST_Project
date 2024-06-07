﻿#include "Game.h"
#include "Player.h"
#include "TreasureChest.h"
#include "UI.h"



/// <summary>
/// コンストラクタ
/// </summary>
UI::UI()
	:	menuGraph			        (-1)
	,	getDirectionModelHandle	(-1)
	,	isHitGemToChest             (false)
    ,   getDirectionCount       (0)
{
	getDirectionModelHandle = MV1LoadModel("data/model/UI/GET!.mv1");
	MV1SetScale(getDirectionModelHandle, VGet(0.05f, 0.05f, 0.0f));
}

/// <summary>
/// デストラクタ
/// </summary>
UI::~UI()
{
	// 3Dモデルハンドルの削除
	MV1DeleteModel(getDirectionModelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void UI::Initialize()
{
	if (menuGraph < 0)
	{
		menuGraph = LoadGraph("data/texture/Menu/GemPiratesMenuGraph.png");
	}
}



/// <summary>
/// UIの更新
/// </summary>
/// <param name="state">ゲームステート</param>
/// <param name="player">プレイヤークラス</param>
/// <param name="clearFlag">クリアしているかどうか</param>
/// <param name="chest">宝箱クラス</param>
/// <param name="nowTimer">ゲームの現在経過時間</param>
void UI::Draw(int state, Player& player, bool& isDrawUIFlag,TreasureChest& chest, float nowTimer)
{
	char _timeCount[256];					// ゲームの経過時間
	// ステートごとに描画を変更
	switch (state)
	{
		// タイトル
	case STATE_MENU:

		// 文字を描画

		// タイトル背景の描画
		DrawGraph(0, 0, menuGraph, true);

		break;

		// ゲーム中
	case STATE_GAME:
		// 現在の経過時間を描画
 		sprintf_s(_timeCount, "～～～%f秒経過～～～", nowTimer);
		DrawString(250, 400, _timeCount, UI_COLOR, true);

		// 「GET!」モデルのポジションを設定
		MV1SetPosition(getDirectionModelHandle, VGet(0,0,0));

        // 宝石獲得演出(宝石が当たっているかつ演出時間ないである)
		if (isHitGemToChest && getDirectionCount <= GET_DIRECTION_DRAW_TIME)
		{
            // 演出時間を経過
            getDirectionCount++;

            // 演出用モデルの描画
			MV1DrawModel(getDirectionModelHandle);
		}
        // 描画指定時間を越えたらゼロに戻す
        if (getDirectionCount >= GET_DIRECTION_DRAW_TIME)
        {
            isDrawUIFlag = false;
            getDirectionCount = 0;
            isHitGemToChest = false;
        }


		break;

		// クリア画面
	case STATE_CLEAR:

		// クリア文字
		// 表示

		break;

		// ゲームオーバー
	case STATE_GAMEOVER:

		// ゲームオーバー文字
		// 表示
		break;

	default:
		break;
	}
}
