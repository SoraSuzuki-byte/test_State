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
	float m_x{};            ///< X座標（左端）
	float m_y{};            ///< Y座標（足元）
	float m_velocityX{};    ///< X方向の速度
	float m_velocityY{};    ///< Y方向の速度
	bool  m_facingRight{true}; ///< 右向きか

	// 攻撃用クールダウン
	float m_attackCooldown{};

	// キー入力
	int m_keyCondition{};   ///< 現在のキー情報（押している間）
	int m_keyTrigger  {};   ///< 押された瞬間のキー情報

	// 状態
	IdleState   m_idle;	    ///< 待機状態の実態
	RunState    m_run;	    ///< 走り状態の実態
	JumpState   m_jump;	    ///< ジャンプ状態の実態
	AttackState m_attack;   ///< 攻撃状態の実態
	PlayerState* m_state{nullptr}; ///< 現在の状態



// メンバ関数の宣言 -------------------------------------------------
public:
// コンストラクタ / デストラクタ
	Player();
	~Player();
// 操作
public:
	// 初期化・更新・描画
	void Initialize();
	void Update(float elapsedTime, int keyCondition, int keyTrigger);
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
	// 攻撃できるかを返す
	bool CanAttack() const;

	// クールダウンタイムのセット
	void StartAttackCooldown();

	// Stateの取得
	PlayerState* GetIdleState()   { return &m_idle; }
	PlayerState* GetRunState()    { return &m_run; }
	PlayerState* GetJumpState()   { return &m_jump; }
	PlayerState* GetAttackState() { return &m_attack; }


	// 位置の取得とセット
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	void  SetX(float x) { m_x = x; }
	void  SetY(float y) { m_y = y; }

	// 速度の取得とセット
	float GetVelocityX() const { return m_velocityX; }
	float GetVelocityY() const { return m_velocityY; }
	void  SetVelocityX(float velocityX) { m_velocityX = velocityX; }
	void  SetVelocityY(float velocityY) { m_velocityY = velocityY; }

	// 向いている向きの取得とセット
	bool IsFacingRight() const { return m_facingRight; }
	void SetFacingRight(bool facingRight) { m_facingRight = facingRight; }
};
