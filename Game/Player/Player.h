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
#include <memory>


// ヘッダファイルの読み込み ===================================================
#include "PlayerState.h"



// クラスの定義 ===============================================================
/**
 * @brief プレイヤー（DrawBoxで表現）
 */
class Player
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr float GROUND_Y = 400.0f;   ///< 地面のY座標（足元の位置）
	static constexpr float WIDTH    = 40.0f;    ///< 幅
	static constexpr float HEIGHT   = 60.0f;    ///< 高さ


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
	std::unique_ptr<PlayerState> m_state;   ///< 現在の状態


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
	void ChangeState(std::unique_ptr<PlayerState> nextState);

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
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	void  SetY(float y) { m_y = y; }

	float GetVelocityY() const { return m_velocityY; }
	void  SetVelocityY(float velocityY) { m_velocityY = velocityY; }

	bool IsFacingRight() const { return m_facingRight; }
	void SetFacingRight(bool facingRight) { m_facingRight = facingRight; }
};
