#pragma once

#include "DxLib.h"

/// <summary>
/// スカイドーム
/// </summary>
class SkyDome
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SkyDome();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SkyDome();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 回転アニメーションン再生
    /// </summary>
    void PlayRotateAnimation();

    // モデルハンドルの取得
    int GetModelHandle() { return modelHandle; }

    // ポジションのgetter/setter.
    const VECTOR& GetPos() const { return pos; }
    const int GetWidth() { return w; }
    const int GetHeight() { return h; }
    void SetPos(const VECTOR set) { pos = set; }

private:
    // 定数
    static constexpr int ROTATION_SPEED = 100;      // 回転速度

    // 変数
    int     modelHandle;        // モデルハンドル
    int     textureHandle;      // テクスチャハンドル
    VECTOR  pos;                // ポジション
    VECTOR  dir;                // 方向
    VECTOR  scale;              // 拡大率
    int     w;                  // 幅
    int     h;                  // 高さ
    int     rotationRateCount;  // 回転させるためのカウント
};


