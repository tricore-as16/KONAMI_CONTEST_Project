#pragma once
#include "SceneBase.h"

class ClearSceneUI;
class TreasureChest;
class GemManager;
class Collision;
class Camera;
class SkyDome;
class BoatWithChest;
class Sea;
class Player;
class EffectManager;


/// <summary>
/// クリアシーン
/// </summary>
class ClearScene : public SceneBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ClearScene(int _score, int _highScore);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ClearScene() override;

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// シーンのアップデート
    /// </summary>
    /// <returns>次のシーンのポインタ</returns>
    SceneBase* UpdateScene() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// UIの描画
    /// </summary>
    void DrawUI() override;

private:
    // 定数
    // クリアシーンでの宝箱の初期化座標
    static constexpr VECTOR TREASURE_CHEST_INITIALIZE_POSITION = { -10.0f,1.5f,-5.0f };
    // クリアシーンでの宝箱の初期回転率
    static constexpr VECTOR TREASURE_CHEST_INITIALIZE_ROTATION_RATE = { 0.0f, 0.0f, 0.0f };
    // クリアシーンでの宝石の乗るボートの初期化座標
    static constexpr VECTOR BOAT_WITH_CHEST_INITIALIZE_POSITION = { -9.0f,-0.5f,-5.0f };
    // クリアシーンでのプレイヤーの初期座標
    static constexpr VECTOR PLAYER_INITILIZE_POSITION = { -15.0f, 1.0f, -5.0f };
    // クリアシーンでのプレイヤーの回転率
    static constexpr VECTOR PLAYER_INITILIZE_ROTATION_RATE = { 0.0f, 0.0f, 0.0f };
    // クリアシーンでのプレイヤーのスケール
    static constexpr VECTOR PLAYER_INITILIZE_SCALE = { 0.03f, 0.03f, 0.03f };

    // 変数
    ClearSceneUI*   clearSceneUI;       // クリアシーンで使用するUI
    TreasureChest*  treasureChest;      // 宝箱
    GemManager*     gemManager;         // 宝石マネージャー
    Camera*         camera;             // カメラ
    SkyDome*        skyDome;            // スカイドーム
    BoatWithChest*  boatWithChest;      // 宝箱を乗せる船
    Sea*            sea;                // 海
    Player*         player;             // プレイヤー
    EffectManager*  effectManager;      // エフェクトマネージャー
};


