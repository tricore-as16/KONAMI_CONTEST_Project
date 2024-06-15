﻿#pragma once
#include "DxLib.h"


/// <summary>
/// シーンベース
/// </summary>
class SceneBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase();   // 仮想関数

    /// <summary>
    /// 初期化
    /// </summary>
    virtual void Initialize() abstract; // 純粋仮想関数

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() abstract; // 純粋仮想関数

    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() abstract;   // 純粋仮想関数

    /// <summary>
    /// UIの描画
    /// </summary>
    virtual void DrawUI() abstract;

private:

};


