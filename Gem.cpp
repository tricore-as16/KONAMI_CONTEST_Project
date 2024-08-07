﻿#include "Calculation.h"
#include "GemManager.h"
#include "Gem.h"


/// <summary>
/// コンストラクタ
/// </summary>
Gem::Gem()
	: modelHandle			    (-1)
	, visibleFlag			    (false)
	, width					    (0.5f)
	, height				    (0.5f)
	, speed					    (0)
	, isHitPlayer			    (false)
	, isHitGround			    (false)
	, fallSpeed				    (0)
	, rotateCount			    (0)
	, gemType				    (0)
	, scaleAdjust			    (0.02f)
    , statusWithPlayer          (NORN)
    , statusWithTreasureChest   (NORN)
    , useState                  (UN_USED)
{
    collisionGraph = LoadGraph("data/texture/Debug/TestHitGraph100x100Green.png");
	pos = VGet(0, 0, 0);
	dir = VGet(0, 0, 0);
	contactDir = VGet(0, 0, 0);
	scale = VGet(0.03f, 0.03f, 0.03f);
}

/// <summary>
/// デストラクタ
/// </summary>
Gem::~Gem()
{
	// 3Dモデルの削除
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// タイプごとの移動アルゴリズムの設定
/// </summary>
/// <param name="gemTyep">宝石の種類</param>
/// <returns>そのタイプの移動方向</returns>
VECTOR Gem::SettingMoveType(int gemTyep)
{
	// 返り値用方向
	VECTOR reDir = VGet(0, 0, 0);
    VECTOR touchesOne = VGet(1.0f, 0.5f, 0.0f);     // １回タッチでゲット
    VECTOR touchesTwo = VGet(0.25f, 0.8f, 0.0f);    // ２回タッチでゲット
    VECTOR touchesFour = VGet(0.12f, 0.8f, 0.0f);   // ４回タッチでゲット

	// 宝石のタイプを受けて方向を設定
	switch (gemType)
	{
		// エメラルド
	case GemManager::EMERALD:
        // １回タッチでゲット
		reDir = touchesOne;
		break;

		// ルビー
	case GemManager::RUBY:
        // ２回タッチでゲット
		reDir = touchesTwo;
		break;
		
		// サファイア
	case GemManager::SAPPHIRE:
        // ２回タッチでゲット
		reDir = touchesTwo;
		break;
		
		// ダイアモンド
	case GemManager::DIAMOND:
        // ４回タッチでゲット
		reDir = touchesFour;
		break;

		// その他
	default:
		break;
	}

	// そのタイプの方向を返す
	return reDir;
}


/// <summary>
/// 宝石のタイプ別で落下速度を設定
/// </summary>
/// <param name="gemType">宝石のタイプ</param>
/// <returns>落下速度</returns>
float Gem::SettingFallSpeedType(int gemType)
{
	// 返り値
	float reFallSpeed = 0;
	
	// タイプ別に落下速度を設定
	switch (gemType)
	{
		// エメラルド
	case GemManager::EMERALD:
		fallSpeed = 0.001f;
		break;

		// ルビー
	case GemManager::RUBY:
		fallSpeed = 0.001f;
		break;

		// サファイア
	case GemManager::SAPPHIRE:
		fallSpeed = 0.001f;
		break;

		// ダイアモンド
	case GemManager::DIAMOND:
		fallSpeed = 0.05f;
		break;

		// その他
	default:	
		break;
	}

	// 設定した落下速度
	return reFallSpeed;
}


void Gem::Initialize(int _modelHandel)
{
    // 3Dモデル設定
    // ベースのモデルの情報をもとにモデルをロード
    modelHandle = MV1DuplicateModel(_modelHandel);

    // ステータス情報
    pos = entryPosition;					// 宝石マネージャーで設定した初期座標
    dir = VGet(0, 0, 0);					// 方向の設定
    contactDir = SettingMoveType(gemType);	// 宝石のタイプのプレイヤーと当たった時の方向を設定
    fallSpeed = SettingFallSpeedType(gemType);	// 落下速度をタイプごとに設定
    MV1SetScale(modelHandle, scale);		// スケールの設定
    scaleAdjust = 0.02f;					// スケールの調整用
    rotateCount = 0;						// 回転率
    statusWithPlayer = NORN;                   // プレイヤーとの状態
    statusWithTreasureChest = NORN;            // 宝箱との状態

    // フラグ
    isHitPlayer = false;		// プレイヤーと接触したか
    visibleFlag = false;		// 存在しているか
    isHitGround = false;		// 地上と接触したか
    isHitPlayer = false;		// プレイヤーと接触中か
}

/// <summary>
/// 宝石の更新
/// </summary>
/// <param name="cal">計算クラス</param>
/// <param name="nowTimer">現在の経過時間</param>
void Gem::Update(Calculation& cal, float nowTimer)
{
	// 登場時間になったら存在
	if(entryTime <= nowTimer && !isHitTreasureChest)
	{
		visibleFlag = true;
	}
	// 地面と接触したら消す
	if (isHitGround)
	{
		visibleFlag = false;
	}

	// 存在する時に更新
	if (visibleFlag)
	{
        // 宝石の回転更新
        UpdateRotation();

        // 重力処理
        UpdateGravity();

		// プレイヤーと接触したら
		if (isHitPlayer)
		{
            // 初めて接触したときしか落下速度は変更しない
            if (statusWithPlayer == ENTER)
            {
			    fallSpeed = +JUMP_POWER;
            }
			dir = VAdd(dir, contactDir);	// 宝石ごとに違う方向
			isHitGround = false;
		}
        else
        {
			isHitPlayer = false;
        }

        // 状態の変化
        // プレイヤー
        statusWithPlayer = (GEM_HIT_STATE)UpdateGemHitState((GEM_HIT_STATE)statusWithPlayer, isHitPlayer);
        // 宝箱
        statusWithTreasureChest = (GEM_HIT_STATE)UpdateGemHitState((GEM_HIT_STATE)statusWithTreasureChest, isHitTreasureChest);

        // 移動更新
        UpdateMove();
    }

    // 使用しているかの状態更新
    UpdateGemUseState();

    // バウンド処理
    UpdateBound();

    // 3Dモデルの座標設定
    MV1SetPosition(modelHandle, pos);
}

/// <summary>
/// エンドウェーブでの宝石の更新
/// </summary>
void Gem::UpdateWaveEnd()
{
    // 3Dモデルの座標設定
    MV1SetPosition(modelHandle, END_POSITION);
}

/// <summary>
/// 宝石の２次元での当たり判定を3D空間上で表示
/// </summary>
void Gem::Draw2DBOXCollision()
{
    // 2D四角形当たり判定描画
    DrawBillboard3D(pos, 0.5f, 0.8f, 0.5f, 0, collisionGraph, true);
}

/// <summary>
/// 状態の移行
/// </summary>
/// <param name="state">宝石の状態</param>
/// <param name="withTarget">対象と当たっているかどうか</param>
/// <returns>宝石の対象との接触状態</returns>
int Gem::UpdateGemHitState(GEM_HIT_STATE state, bool withTarget)
{
    // 移行する状態
    auto _shiftState = state;

    // NORN→ENTER (接触した瞬間の状態)
    if (state == NORN && withTarget)
    {
        _shiftState = ENTER;
    }
    // ENTER→STAY (接触し続けている状態)
    else if (state == ENTER && withTarget)
    {
        _shiftState = STAY;
    }
    // STAY→EXIT (接触状態から接触していない状態へ移行した状態)
    else if (state == STAY && !withTarget)
    {
        _shiftState = EXIT;
    }
    // EXIT→NORN (接触していない状態)
    else if (state == EXIT && !withTarget)
    {
        _shiftState = NORN;
    }

    // 移行した状態または、そのままの状態を返す
    return _shiftState;
}

/// <summary>
/// 宝石の情報リセット
/// </summary>
void Gem::ResetGem(VECTOR resetPosition, int constantEntyrTime, int index)
{
    useState = UN_USED;                 // 使用状態
    pos = resetPosition;                // 座標更新
    entryTime = constantEntyrTime * index;
    dir = VGet(0, 0, 0);                // 移動方向
    statusWithPlayer = NORN;            // プレイヤーとの状態
    statusWithTreasureChest = NORN;     // 宝箱との状態
    isHitPlayer = false;                // プレイヤーと接触したか
    visibleFlag = false;                // 存在しているか
    isHitGround = false;                // 地上と接触したか
    isHitPlayer = false;                // プレイヤーと接触中か
}

/// <summary>
/// 宝石の使用状態の更新
/// </summary>
void Gem::UpdateGemUseState()
{
    // エントリー時間になったら
    if (visibleFlag)
    {
        useState = IN_USE;  // 使用中
    }
    // 地面についてスケールがゼロになったら
    if (scaleAdjust <= 0)
    {
        useState = USED;    // 使用済み
    }
    // 宝箱に入ったら
    if (isHitTreasureChest)
    {
        useState = USED;    // 使用済み
    }
}

/// <summary>
/// 宝石の回転更新
/// </summary>
void Gem::UpdateRotation()
{
    // 少しずつ回転１フレームずつ1度回転する
    if (rotateCount <= 360)
    {
        rotateCount++;
    }
    if (rotateCount >= 360)
    {
        rotateCount = 0;
    }
    // 少しずつ回転する
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, rotateCount * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// 移動更新
/// </summary>
void Gem::UpdateMove()
{
    // 正規化
    if (VSquareSize(dir) > 0)
    {
        dir = VNorm(dir);
    }

    // 移動量を出す
    auto velocity = VScale(dir, MOVE_SPEED);

    // 落下速度を移動量に加える
    auto fallVelocity = VGet(0, fallSpeed, 0);
    velocity = VAdd(velocity, fallVelocity);

    // ポジションの更新
    pos = VAdd(pos, velocity);
}

/// <summary>
/// バウンド処理
/// </summary>
void Gem::UpdateBound()
{
    // 床についたら跳ねる
    if (isHitGround)
    {
        //pos.y = 0.1;
        // 重力に逆らう（これやらないと地面貫通する）
        fallSpeed += GRAVITY_POWER * 1.2f;
        scaleAdjust -= 0.0005f;     // 少しづつスケールを小さくする
        // スケールを設定
        MV1SetScale(modelHandle, VGet(scaleAdjust, scaleAdjust, scaleAdjust));
    }
    // スケールがゼロ以下になったら修正
    if (scaleAdjust <= 0)
    {
        scaleAdjust = 0;
    }
}

/// <summary>
/// 重力を掛ける更新
/// </summary>
void Gem::UpdateGravity()
{
    // 落下速度に重力を加算
    fallSpeed -= GRAVITY_POWER;

    // 重力加速度の限界値を越えない
    if (fallSpeed <= -GRAVITY_POWER_LIMIT)
    {
        fallSpeed = -GRAVITY_POWER_LIMIT;
    }

    // 床より下には落ちない
    if (pos.y <= 0.1 && isHitGround == false)
    {
        pos.y = 0.1;			// 座標を地面に固定
        isHitGround = true;		// 地面についている状態
        entryTime = 0;			// 登場時間を強制的にゼロにする
    }
}

/// <summary>
/// 描画
/// </summary>
void Gem::Draw()
{
    // 3Dモデルの描画
    MV1DrawModel(modelHandle);
}
