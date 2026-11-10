/**
 * @file   PlayerConstants.h
 *
 * @brief  Playerの定数をまとめるヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#pragma once

namespace PlayerConstants
{
	// 見た目
	constexpr float GROUND_Y = 400.0f;   ///< 地面のY座標（足元の位置）
	constexpr float WIDTH    = 40.0f;    ///< 幅
	constexpr float HEIGHT   = 60.0f;    ///< 高さ

	// 動き
	constexpr float MOVE_SPEED  = 240.0f;  ///< 移動速度（px/秒）
	constexpr float JUMP_SPEED  = -700.0f; ///< ジャンプの初速（px/秒、上向きが負）
	constexpr float GRAVITY     = 2000.0f; ///< 重力加速度（px/秒^2）
	constexpr float ATTACK_TIME = 0.3f;    ///< 攻撃の持続時間（秒）
	constexpr float ATTACK_COOLDOWN = 0.3f;///< 攻撃のクールダウン（秒）
}