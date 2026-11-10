/**
 * @file   JumpState.cpp
 *
 * @brief  プレイヤーのJump状態のソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#include "pch.h"
#include "Game/Player/PlayerConstants.h"
#include "JumpState.h"
#include "Game/Player/Player.h"



 // ===========================================================================
 // JumpState（ジャンプ）
 // ===========================================================================

/// <summary>
/// このStateに切り替わった瞬間に呼ばれる 関数
/// </summary>
/// <param name="player"></param>
void JumpState::Enter(Player& player)
{
	// 上向きの初速を与える
	player.SetVelocityY(PlayerConstants::JUMP_SPEED);
}


/// <summary>
/// このStateの色を取得する
/// </summary>
/// <returns>このStateの色</returns>
unsigned int JumpState::GetBodyColor() const
{
	return GetColor(255, 220, 60);   // 黄
}

