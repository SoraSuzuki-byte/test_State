/**
 * @file   Player.h
 *
 * @brief  プレイヤーに関するヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// 多重インクルードの防止 =====================================================
#pragma once


// ヘッダファイルの読み込み ===================================================
#include "PlayerState.h"
#include "Game/Player/States/IdleState.h"
#include "Game/Player/States/RunState.h"
#include "Game/Player/States/JumpState.h"
#include "Game/Player/States/AttackState.h"

// クラスの定義 ===============================================================
/**
 * @brief プレイヤー（DrawBoxで表現）
 */
class Player
{
// データメンバの宣言 -----------------------------------------------
private:
	// 位置・速度
	float m_x;              ///< X座標（左端）
	float m_y;              ///< Y座標（足元）
	float m_velocityY;      ///< Y方向の速度（下向きが正）
	bool  m_facingRight;    ///< 右向きか

	int m_keyCondition;   ///< 現在のキー情報（押している間）
	int m_keyTrigger;     ///< 押された瞬間のキー情報

	// 状態
	IdleState   m_idle;	 ///< 待機状態の実態
	RunState    m_run;	 ///< 走り状態の実態
	JumpState   m_jump;	 ///< ジャンプ状態の実態
	AttackState m_attack;///< 攻撃状態の実態
	PlayerState* m_state;   ///< 現在の状態



// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Player();

	// デストラクタ
	~Player();


// 操作
public:
	// 更新処理
	void Update(float elapsedTime, int keyCondition, int keyTrigger);

	// 描画処理
	void Render() const;

	// 状態の変更
	void ChangeState(PlayerState* nextState);

	// X方向に移動（画面外に出ないよう制限する）
	void MoveX(float dx);


// 入力
public:
	// ボタンが押されているか
	bool IsHeld(int button) const;

	// ボタンが押された瞬間か
	bool IsPressed(int button) const;

	// 左右入力（左:-1, なし:0, 右:1）
	int GetMoveDirection() const;


// 取得/設定
public:
	// Stateの取得
	PlayerState* GetIdleState()   { return &m_idle; }
	PlayerState* GetRunState()    { return &m_run; }
	PlayerState* GetJumpState()   { return &m_jump; }
	PlayerState* GetAttackState() { return &m_attack; }

	// 位置の取得とセット
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	void  SetY(float y) { m_y = y; }

	// 速度の取得とセット
	float GetVelocityY() const { return m_velocityY; }
	void  SetVelocityY(float velocityY) { m_velocityY = velocityY; }

	// 向いている向きの取得とセット
	bool IsFacingRight() const { return m_facingRight; }
	void SetFacingRight(bool facingRight) { m_facingRight = facingRight; }
};
