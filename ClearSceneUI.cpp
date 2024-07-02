#include "DxLib.h"
#include "ClearSceneUI.h"
#include "Common.h"


/// <summary>
/// コンストラクタ
/// </summary>
ClearSceneUI::ClearSceneUI()
    : lastFlashingTime         (0)
    , isKeyPleaseGraphDraw  (false)
{
    clearUIGraph = LoadGraph("data/texture/Clear/FrameUINoClearColor.png");
    scoreBoardGraph = LoadGraph("data/texture/Clear/socreResult600x200.png");
    resultsGraph = LoadGraph("data/texture/Clear/ResultsImg.png");
    keyPleaseGraph = LoadGraph("data/texture/State/KeyRelese.png");
}

/// <summary>
/// デストラクタ
/// </summary>
ClearSceneUI::~ClearSceneUI()
{
}

/// <summary>
/// 更新
/// </summary>
void ClearSceneUI::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void ClearSceneUI::Draw(int score, int highScore)
{
    // クリアUI
    DrawGraph(0, 0, clearUIGraph, true);

    // リザルトテキスト
    DrawRotaGraph(SCREEN_SIZE_X / 2, 150, 1, 0, resultsGraph, true);

    // スコアボード
    DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1, 0, scoreBoardGraph, true);

    // クリア文字
    DrawFormatString(600, 400, UI_COLOR, "SCORE : %d", score);
    DrawFormatString(600, 500, UI_COLOR_RED, "HIGHSCORE : %d", highScore);

    // キー入力指示
    DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - (SCREEN_SIZE_Y / 4), 1, 0, keyPleaseGraph, true);
    PlayKeyPleaseTextFlashing();    // 文字点滅表示
}

/// <summary>
/// 文字の描画
/// </summary>
void ClearSceneUI::PlayKeyPleaseTextFlashing()
{
    // 現在時間取得
    int _time = GetNowCount();

    // 点滅表示
    if (_time - lastFlashingTime >= FLASHING_INTERVAL)
    {
        isKeyPleaseGraphDraw = !isKeyPleaseGraphDraw;
        lastFlashingTime = _time;          // 最後に点滅させた時間を記録
    }
    if (isKeyPleaseGraphDraw)
    {
        // キーを入力してください
        DrawFormatString(475, SCREEN_SIZE_Y - (SCREEN_SIZE_Y / 4) - 25, UI_COLOR, "Press Any Button to Start");
    }
}
