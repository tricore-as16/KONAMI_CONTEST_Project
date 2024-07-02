#pragma once
#include "Common.h"
#include "StageObjectBase.h"

class EffectManager;

/// <summary>
/// 海
/// </summary>
class Sea : public StageObjectBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Sea();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Sea();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 波のアニメーションを再生
    /// </summary>
    void PlayWaveAnimation();

    /// <summary>
    /// クリアシーンでの更新
    /// </summary>
    void UpdateClearScene();

private:
    // 定数
    static constexpr float SCALE_ADD = 0.000002f;                           // スケールを加算する値
    static constexpr float SCALE_ADD_MAX_LIMIT = 0.00009f;                  // スケールの最大加算値
    static constexpr float SCALE_ADD_MIN_LIMIT = -0.00009f;                 // スケールの最小加算値
    static constexpr VECTOR FIRE_WORKS_EFFECT_PLAY_POSITION = { -7,0, 50};  // 花火のエフェクトを再生する座標
    static constexpr int FIRE_WORKS_EFFECT_PLAY_CYCLE = 400;                // 花火のエフェクトを再生する周期

    // 変数
    EffectManager* effectManager;   // エフェクトマネージャー
    int effectCount;                // エフェクトをループさせるためのカウント
    float waveAnimationScaleY;      // 波のアニメーション用Yスケール
    bool isScaleDown;               // スケールを小さくするかどうか
};

