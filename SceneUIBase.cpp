﻿#include "Common.h"
#include "SceneUIBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneUIBase::SceneUIBase()
{
    blackOutGraph = LoadGraph("data/texture/State/BlackOutGraph.png");
    screenBrightness = 1;
    isBlackOut = false;
    fadeState = FADE_NONE;
}

/// <summary>
/// デストラクタ
/// </summary>
SceneUIBase::~SceneUIBase()
{
    // 画像の削除
    DeleteGraph(blackOutGraph);
}

void SceneUIBase::Update()
{

}

/// <summary>
/// フェードインUIのみ（UIの明るさを徐々にあげる）
/// </summary>
/// ToDo:ほかのフェード関数と内容がかぶっているが一旦スルー
void SceneUIBase::StartFadeInUI()
{
    // 画像の濃さをあげる
    if (screenBrightness < TRANSPARENCY_LIMIT)
    {
        screenBrightness += ADD_TRANSPARENCY;
    }
    // 画像の濃さを設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenBrightness);

    // フェードが終了したことを伝える
    if (screenBrightness >= TRANSPARENCY_LIMIT)
    {
        fadeState = FADE_IN_UI_END;
    }
    else
    {
        //fadeState = FADE_PLAYING;
    }
}

/// <summary>
/// フェードアウトUIのみ（UIの明るさを徐々に下げる）
/// </summary>
void SceneUIBase::StartFadeOutUI()
{
    // 画面の明るさが最大値であれば初期化する
    if (screenBrightness == 255)
    {
        screenBrightness = 0;
        // 画像の濃さを設定
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenBrightness);
    }

    // 画像の濃さをあげる
    if (screenBrightness < TRANSPARENCY_LIMIT)
    {
        screenBrightness += ADD_BLACK_OUT_ADD_TRANSPARENCY;
    }

    // 画像の濃さを設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, -screenBrightness + TRANSPARENCY_LIMIT);

    // フェードが終了したことを伝える
    if (screenBrightness >= TRANSPARENCY_LIMIT)
    {
        fadeState = FADE_OUT_UI_END;
    }
    else
    {
        fadeState = FADE_OUT_UI_PLAYING;
    }
}

/// <summary>
/// フェードイン画面のみ（画面の明るさを徐々に上げる）
/// </summary>
/// NOTE:３D空間含めてフェードアウトすることが困難なため
/// 　   黒画像を画面サイズ100%から0%に徐々にスケールダウンさせることで
///      フェードインと同様の見た目に処理
void SceneUIBase::StartFadeInScreen()
{
    // 画面の明るさが初期化されていれば
    if (screenBrightness == 1)
    {
        screenBrightness = 255;
        // 画像の濃さを設定
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenBrightness);
    }

    // 画像の濃さをあげる
    if (screenBrightness > 0)
    {
        screenBrightness -= FADE_OUT_SCREEN_SPEED;
    }

    // 明るさの比率から画像サイズを縮小する
    float _graphScale = (float)screenBrightness / FADE_IN_SCREEN_SCALE_RATE;
    // 真っ黒の画像を描画(中心座標指定描画)
    DrawRotaGraph(800, 480, _graphScale, 0, blackOutGraph,true);

    // 画像の濃さを設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenBrightness);

    // フェードが終了したことを伝える
    if (screenBrightness <= 0)
    {
        fadeState = FADE_IN_SCREEN_END;
    }
    else
    {
        fadeState = FADE_IN_SCREEN_PLAYING;
    }
}

/// <summary>
/// フェードアウト画面のみ（画面の明るさを徐々に下げる）
/// </summary>
void SceneUIBase::StartFadeOutScreen()
{
    // 真っ黒の画像を描画
    DrawGraph(0, 0, blackOutGraph, true);

    // 画面の明るさが最大値であれば初期化する
    if (screenBrightness == 255)
    {
        screenBrightness = 0;
        // 画像の濃さを設定
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenBrightness);
    }

    // 画像の濃さをあげる
    if (screenBrightness < TRANSPARENCY_LIMIT)
    {
        screenBrightness += ADD_BLACK_OUT_ADD_TRANSPARENCY;
    }

    // 画像の濃さを設定
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, -screenBrightness + TRANSPARENCY_LIMIT);


    // フェードが終了したことを伝える
    if (screenBrightness >= TRANSPARENCY_LIMIT)
    {
        fadeState = FADE_OUT_SCREEN_END;
    }
    else
    {
        fadeState = FADE_OUT_SCREEN_PLAYING;
    }

}

/// <summary>
/// 画面中央に文字を描画
/// </summary>
/// <param name="string">描画したい文字列が格納されたchar型変数</param>
/// <param name="drawPosition">描画したいY座標位置</param>
/// <param name="uiColor">UIの色</param>
/// MEMO:数値も同時に描画したい場合はsnprintfを使い、
///      数値を代入後、第一引数に渡してください。
void SceneUIBase::DrawStringCenterScreen(char* string, int drawPositionY,int uiColor)
{
    // 文字の長さを取得
    int stringLength = strlen(string);

    // 文字列の描画幅を取得
    int stringWidth = GetDrawStringWidth(string, stringLength);

    // 描画する座標を設定
    int screenCenterX = SCREEN_SIZE_X / 2;
    int drawPositionX = screenCenterX - (stringWidth / 2);

    // 中央に描画
    DrawString(drawPositionX, drawPositionY, string, uiColor, true);
}
