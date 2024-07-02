#pragma once
#include "DxLib.h"

class Game;
class Enemy;
class EffectManager;
class PlayerOar;
class PlayerBoat;
class PlayerCushion;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final
{
public:
    /// <summary>
    /// アニメーションタイプ
    /// </summary>
    enum ANIMATION_TYPE
    {
        SITTEING,       // 座る
        DELIGHTED,      // 喜ぶ
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Player();

    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="initializePosition">初期化座標</param>
    /// <param name="rotationRate">初期化回転率</param>

    void Initialize(VECTOR initializePosition, VECTOR rotationRate,
        int attachIndex,VECTOR initializeScale);

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

    /// 装備品モデルの座標設定
    /// </summary>
    void SetPositionAssetModle();

    /// <summary>
    /// プレイヤーの当たり判定描画2DBOX
    /// </summary>
    void Draw2DBOXCollision();

    /// <summary>
    /// プレイヤーの描画
    /// </summary>
    void Draw();

    /// <summary>
    /// プレイヤー装備品描画
    /// </summary>
    void DrawPlayerAssetModel();

    /// <summary>
    /// クリアシーンでの更新
    /// </summary>
    void UpdateClearScene();

    /// <summary>
    /// クリアシーンでの描画
    /// </summary>
    void DrawClearScene();

    // getter/setter
    const VECTOR& GetPos() const { return pos; }
    const float GetWidth() { return width; }
    const float GetHeight() { return height; }
    const float GetRadius() { return r; }
    const VECTOR GetPlayerCushionOffSetPosition()const { return playerCushionOffsetPosition; }

    void SetIsHitGem(const bool set) { isHitGem = set; }

private:
    // 定数
    static constexpr float HIT_BOX_WIDTH = 4.5f;                    // 当たり判定の幅
    static constexpr float HIT_BOX_HEIGHT = 4.0f;                   // 当たり判定の高さ
    static constexpr float GRAVITY = 0.5f;                          // キャラに掛かる重力加速度
    static constexpr float JUMP_POWER = 25.0f;                      // キャラのジャンプ力
    static constexpr float SMALL_JUMP_POWER = 17.0f;                // 小ジャンプ力
    static constexpr int MOVE_LIMIT_Y = 820;                        // キャラのY座標の移動制限
    static constexpr float SPEED = 0.35f;                           // キャラの移動スピード
    static constexpr int MOVE_SIDE_LIMIT_MIN = -20;                 // 横の移動制限(カメラから見て左)
    static constexpr int MOVE_SIDE_LIMIT_MAX = -4;                  // 横の移動制限(カメラから見て右)
    static constexpr int ANIMATION_PLAYBUCK_SPEED = 2;              // アニメーションの再生時間
    static constexpr VECTOR LEFT_DIRECTION = { -1.0f,0.0f,0.0f };   // 左方向ディレクション
    static constexpr VECTOR RIGHT_DIRECTION = { 1.0f,0.0f,0.0f };   // 右方向ディレクション
    static constexpr VECTOR NO_DIRECTION = { 0.0f,0.0f,0.0f };      // 方向無し

    // 変数
    EffectManager* effectManager;   // エフェクト管理
    
    // ハンドル
    int     modelHandle;            // モデルハンドル
    int     collisionGraph;         // 当たり判定用画像

    // 情報
    VECTOR  pos;                    // ポジション
    VECTOR  dir;                    // 方向
    VECTOR  scale;                  // スケール
    VECTOR  rotationRate;           // 回転率
    float   width;                  // 幅
    float   height;                 // 高さ
    float   fallSpeed;              // 落下速度
    float   speed;                  // 移動スピード

    // 当たり判定
    float   r;                      // 球型当たり判定の半径
    bool    isHitGem;               // ジェムと接触したか

    // アニメーション関係
    int     animationPlayTime;      // アニメーションの再生管理時間(これをインクリメントして再生する)
    int     animationAttachIndex;   // 再生したいアニメーション番号(アタッチする用)
    int     animationPlayTotalTime; // 再生したいアニメーションの総再生時間

    // 装備品
    PlayerOar*      playerOar;
    PlayerBoat*     playerBoat;
    PlayerCushion*  playerCushion;
    VECTOR          playerCushionOffsetPosition;
};

