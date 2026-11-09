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
#include "IdleState.h"
#include "RunState.h"



 // ===========================================================================
 // JumpState（ジャンプ）
 // ===========================================================================
void JumpState::Enter(Player& player)
{
	// 上向きの初速を与える
	player.SetVelocityY(PlayerConstants::JUMP_SPEED);
}

PlayerState* JumpState::Update(Player& player, float elapsedTime)
{
	// 空中でも左右に動ける
	const int direction = player.GetMoveDirection();
	if (direction != 0)
	{
		player.SetFacingRight(direction > 0);
		player.MoveX(direction * PlayerConstants::MOVE_SPEED * elapsedTime);
	}

	// 重力
	player.SetVelocityY(player.GetVelocityY() + PlayerConstants::GRAVITY * elapsedTime);
	player.SetY(player.GetY() + player.GetVelocityY() * elapsedTime);

	// 着地
	if (player.GetY() >= PlayerConstants::GROUND_Y)
	{
		player.SetY(PlayerConstants::GROUND_Y);
		player.SetVelocityY(0.0f);

		if (direction != 0)
		{
			return player.GetRunState();
		}
		return player.GetIdleState();
	}

	return nullptr;
}

unsigned int JumpState::GetBodyColor() const
{
	return GetColor(255, 220, 60);   // 黄
}

