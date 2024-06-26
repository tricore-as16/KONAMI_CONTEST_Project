﻿#include "Common.h"
#include "MenuSceneUI.h"


/// <summary>
/// コンストラクタ
/// </summary>
MenuSceneUI::MenuSceneUI()
{
    SetFontSize(UI_FONT_SIZE);  // フォントサイズ設定
    titileGraph = LoadGraph("data/texture/Menu/GemPiratesMenuGraph.png");
}

/// <summary>
/// デストラクタ
/// </summary>
MenuSceneUI::~MenuSceneUI()
{
    DeleteGraph(titileGraph);
}

/// <summary>
/// 更新
/// </summary>
void MenuSceneUI::Update()
{
    // 処理なし
}

/// <summary>
/// 描画
/// </summary>
void MenuSceneUI::Draw(int highScore)
{
    // メニュー画像（タイトル画像の描画）
    DrawGraph(0, 0, titileGraph, true);

    DrawFormatString(200, SCREEN_SIZE_Y - 300, GetColor(255, 255, 255), "Press Any Button to Start");

    // スコア描画
    DrawFormatString(450, 500, UI_COLOR_WHITE, "HIGHSCORE : %d", highScore);
}


