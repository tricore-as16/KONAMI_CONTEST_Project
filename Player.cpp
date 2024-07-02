#include "Player.h"
#include "Enemy.h"
#include "EffectManager.h"
#include "Game.h"
#include "PlayerOar.h"
#include "PlayerBoat.h"
#include "PlayerCuhion.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
    :   isHitGem                (false)
    ,   speed                   (5)
    ,   r                       (1)
    ,   width                   (HIT_BOX_WIDTH)
    ,   height                  (HIT_BOX_HEIGHT)
    ,   collisionGraph          (-1)
    ,   animationPlayTime       (0)
    ,   fallSpeed               (0.0f)
    ,   pos                     (VGet(-18, 0, -5))
    ,   dir                     (VGet(0, 0, 0))
    ,   scale                   (VGet(0.02f, 0.02f, 0.02f))
    ,   rotationRate            (VGet(0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f))
{
    effectManager = EffectManager::GetInstance();
    modelHandle = MV1LoadModel("data/model/player/PlayerModle.mv1");
    animationAttachIndex = MV1AttachAnim(modelHandle, SITTEING, -1, false);
    animationPlayTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animationAttachIndex);
    collisionGraph = LoadGraph("data/texture/Debug/TestHitGraph100x100Red.png");
    MV1SetRotationXYZ(modelHandle, rotationRate);
    MV1SetScale(modelHandle, scale);

    // プレイヤー装備品
    playerOar = new PlayerOar();
    playerBoat = new PlayerBoat();
    playerCushion = new PlayerCushion();
    playerCushionOffsetPosition = playerCushion->GetOffSetPosition();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
    MV1DeleteModel(modelHandle);
    delete(playerOar);
    delete(playerBoat);
    delete(playerCushion);
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(VECTOR initializePosition, VECTOR rotationRate,
    int attachIndex, VECTOR initializeScale)
{
    // 座標設定
    pos = initializePosition;
    // モデルの回転(違和感ない位置に修正)
    MV1SetRotationXYZ(modelHandle, rotationRate);
    // アニメーションのアタッチ
    animationAttachIndex = MV1AttachAnim(modelHandle, DELIGHTED, -1, false);
    // スケールの設定
    MV1SetScale(modelHandle, initializeScale);
}

/// <summary>
/// プレイヤーの更新
/// </summary>
void Player::Update()
{
    // 移動
    UpdateMovement();

    // 宝石と接触したらエフェクト再生
    if (isHitGem)
    {
        // 再生位置はクッションの座標
        VECTOR _playPos = VAdd(pos, playerCushionOffsetPosition);
        _playPos = VAdd(_playPos, VGet(0.0f, 1.3f, 0.0f));  // 少し上
        effectManager->PlayPlayerHitEffect(_playPos);
    }

    // アニメーションの更新
    UpdateAnimation();

    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, pos);

    // プレイヤー装備品のポジション設定
    SetPositionAssetModle();
}

/// <summary>
/// 装備品モデルの座標設定
/// </summary>
void Player::SetPositionAssetModle()
{
    playerOar->Update(pos);     // オール
    playerBoat->Update(pos);    // ボート
    playerCushion->Update(pos); // クッション
}

/// <summary>
/// 移動更新
/// </summary>
void Player::UpdateMovement()
{
    // キー入力取得
    auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // 無限に移動しないように停止
    dir = NO_DIRECTION;

    if (CheckHitKey(KEY_INPUT_LEFT) == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0)
    {
        dir = VAdd(dir, LEFT_DIRECTION);
        speed = SPEED;
    }
    else if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0)
    {
        dir = VAdd(dir, RIGHT_DIRECTION);
        speed = SPEED;
    }

    // 正規化
    if (VSquareSize(dir) > 0)
    {
        dir = VNorm(dir);
    }

    // 移動量を出す
    auto velocity = VScale(dir, speed);

    // 移動
    pos = VAdd(pos, velocity);

    // 方向調整
    if (VSize(velocity) != 0)
    {
        dir = VNorm(velocity);
    }

    // 移動制限
    LimitingMovement();

}

/// <summary>
/// 移動制限
/// </summary>
void Player::LimitingMovement()
{
    if (pos.x >= MOVE_SIDE_LIMIT_MAX)
    {
        pos.x = MOVE_SIDE_LIMIT_MAX;
    }
    if (pos.x <= MOVE_SIDE_LIMIT_MIN)
    {
        pos.x = MOVE_SIDE_LIMIT_MIN;
    }
}

/// <summary>
/// アニメーションの更新
/// </summary>
void Player::UpdateAnimation()
{
    // 再生時間を進める
    animationPlayTime += ANIMATION_PLAYBUCK_SPEED;

    // 現在の再生時間が総再生時間に達したらゼロに戻す
    if (animationPlayTime >= animationPlayTotalTime)
    {
        animationPlayTime = 0;
    }

    // 再生時間のセット
    MV1SetAttachAnimTime(modelHandle, animationAttachIndex, animationPlayTime);
}

/// <summary>
/// プレイヤーの当たり判定描画2DBOX
/// </summary>
void Player::Draw2DBOXCollision()
{
    DrawBillboard3D(pos, 0.5f, 0.9f, 4.0f, 0, collisionGraph, true);
}

/// <summary>
/// プレイヤーの描画
/// </summary>
void Player::Draw()
{
    // プレイヤー
    MV1DrawModel(modelHandle);
    // プレイヤー装備品
    DrawPlayerAssetModel();
}

/// <summary>
/// プレイヤー装備品描画
/// </summary>
void Player::DrawPlayerAssetModel()
{
    playerOar->Draw();      // オール
    playerBoat->Draw();     // ボート
    playerCushion->Draw();  // クッション
}

/// <summary>
/// クリアシーンでの更新
/// </summary>
void Player::UpdateClearScene()
{
    // アニメーション更新
    UpdateAnimation();

    // 座標の更新
    MV1SetPosition(modelHandle, pos);
}

/// <summary>
/// クリアシーンでの描画
/// </summary>
void Player::DrawClearScene()
{
    MV1DrawModel(modelHandle);
}
