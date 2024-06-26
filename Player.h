﻿#define _PLAYER_H_

#include "DxLib.h"

class Game;
class Enemy;
class EffectManager;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Player();

    /// <summary>
    /// プレイヤーの初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// プレイヤーの更新
    /// </summary>
    void Update();

    /// <summary>
    /// 移動更新
    /// </summary>
    void UpdateMovement();

    /// <summary>
    /// 移動制限
    /// </summary>
    void LimitingMovement();

    /// <summary>
    /// アニメーションの更新
    /// </summary>
    void UpdateAnimation();

    /// <summary>
    /// プレイヤーの当たり判定描画2DBOX
    /// </summary>
    void Draw2DBOXCollision();

    /// <summary>
    /// プレイヤーの描画
    /// </summary>
    void Draw();

    // ポジションのgetter/setter.
    const VECTOR& GetPos() const { return pos; }
    const float GetWidth() { return width; }
    const float GetHeight() { return height; }
    const float GetRadius() { return r; }

    void SetIsHitEnemy(const bool set) { isHitEnemy = set; }
    void SetIsHitGem(const bool set) { isHitGem = set; }

private:
    // 定数
    static constexpr float GRAVITY = 0.5f;			    // キャラに掛かる重力加速度
    static constexpr float JUMP_POWER = 25.0f;		    // キャラのジャンプ力
    static constexpr float SMALL_JUMP_POWER = 17.0f;	// 小ジャンプ力
    static constexpr int	MOVE_LIMIT_Y = 820;		    // キャラのY座標の移動制限
    static constexpr float SPEED = 0.35f;			    // キャラの移動スピード
    static constexpr int MOVE_SIDE_LIMIT_MIN = -18;     // 横の移動制限(カメラから見て左)
    static constexpr int MOVE_SIDE_LIMIT_MAX = 1;       // 横の移動制限(カメラから見て右)
    static constexpr int ANIMATION_PLAYBUCK_SPEED = 2;  // アニメーションの再生時間

    // 変数
    EffectManager* effectManager;   // エフェクト管理
    
	// ハンドル
	int		modelHandle;	// モデルハンドル
    int     collisionGraph; // 当たり判定用画像

    // 情報
	VECTOR	pos;			// ポジション.
	VECTOR	dir;			// 方向
	VECTOR	scale;			// スケール
    float   width;          // 幅
    float   height;         // 高さ
	float	fallSpeed;		// 落下速度
	float	speed;			// 移動スピード
	// フラグ
	bool	isGround;		// プレイヤーが接地中か
	bool	isHitTop;		// プレイヤーの頭が天井に当たっているか
	bool	isGreatJump;	// ジャンプが成功したか
	// 当たり判定
	float		r;			// 球型当たり判定の半径
	bool	isHitEnemy;		// エネミーと接触したか
	bool	isHitGem;		// ジェムと接触したか
    // アニメーション関係
    int     animationPlayTime;      // アニメーションの再生管理時間(これをインクリメントして再生する)
    int     animationAttachIndex;   // 再生したいアニメーション番号(アタッチする用)
    int     animationPlayTotalTime; // 再生したいアニメーションの総再生時間
};

