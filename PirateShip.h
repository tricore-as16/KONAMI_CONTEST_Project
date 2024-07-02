#pragma once
#include "StageObjectBase.h"

class EffectManager;

/// <summary>
/// 海賊船
/// </summary>
class PirateShip : public StageObjectBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PirateShip();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PirateShip();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    // 描画
    void Draw() override;

private:
    // 定数
    static constexpr int PIRATE_SHIP_BURNS_SMALL_EFFECT_CYCLE = 140;    // 海賊船が燃えるエフェクト(中)を再生する周期
    static constexpr int THUNDER_EFFECT_CYCLE = 300;                    // 雷のエフェクトを再生する周期
    static constexpr int THUNDER_EFFECT_POSITION_X_OFFSET = 30;         // 雷のエフェクトを再生する位置のX軸ずらし量
    static constexpr int THUNDER_EFFECT_RANDOM_RANGE = 25;              // 雷のエフェクトを再生するX軸の乱数の範囲
    static constexpr VECTOR PIRATE_SHIP_BURNS_SMALL_EFFECT_POSITION_1 = { 21,-21,-2 };  // 海賊船が燃えるエフェクト(小)を再生する座標１
    static constexpr VECTOR PIRATE_SHIP_BURNS_SMALL_EFFECT_POSITION_2 = { 20,-20,-5 };  // 海賊船が燃えるエフェクト(小)を再生する座標１
    static constexpr VECTOR PIRATE_SHIP_BURNS_SMALL_EFFECT_POSITION_3 = { 25,-19,-0 };  // 海賊船が燃えるエフェクト(小)を再生する座標１
    static constexpr VECTOR THUNDER_EFFECT_POSITION = { 0,-25,10 };                     // 雷のエフェクトを再生する座標

    // 変数
    int effectCount;                    // エフェクトをループ再生するためのカウント
    EffectManager* effectManager;       // エフェクトマネージャー
};


