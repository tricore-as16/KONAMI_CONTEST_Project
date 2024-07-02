#pragma once
#include "DxLib.h"
#include "SceneUIBase.h"

/// <summary>
/// クリアシーンUI
/// </summary>
class ClearSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ClearSceneUI();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ClearSceneUI();

    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(int score,int highScore);

    /// <summary>
    /// 文字の点滅
    /// </summary>
    void PlayKeyPleaseTextFlashing();

private:
    // 定数
    const int UI_COLOR = GetColor(20, 20, 10);      // UIの色
    const int UI_COLOR_RED = GetColor(255, 0, 0);   // UIの色(赤)
    static constexpr int FLASHING_INTERVAL = 500;   // 文字点滅の間隔(GetNowCountなのでミリ秒)

    // 変数
    int     clearUIGraph;           // クリアした時のUI画像
    int     scoreBoardGraph;        // スコアボード画像
    int     resultsGraph;           // リザルト画像
    int     keyPleaseGraph;         // キー入力指示画像
    int     lastFlashingTime;          // 最後に点滅した時間
    bool    isKeyPleaseGraphDraw;   // 文字が描画されているか
};


