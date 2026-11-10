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




/// <summary>
/// 更新
/// </summary>
/// <param name="player">Playerの参照</param>
/// <param name="elapsedTime">経過時間</param>
/// <returns>切り替わるState</returns>
PlayerState* JumpState::Update(Player& player, float elapsedTime)
{
	// 空中でも左右に動ける
	const int direction = player.GetMoveDirection();

	// X軸方向の速度 = 入力方向 × 速さ
	const float velocityX = (direction) * (PlayerConstants::MOVE_SPEED);

	// X軸方向の速度をセット
	player.SetVelocityX(velocityX);

	// もし移動の向きがあれば
	if (direction != 0)
	{
		player.SetFacingRight(direction > 0);
		player.MoveX(velocityX * elapsedTime);
	}

	// 重力を適応
	if (player.ApplyGravityAndLand(elapsedTime)) //着地していれば
	{
		if (direction != 0)
		{
			return player.GetRunState();
		}
		return player.GetIdleState();
	}


	// 攻撃（Xキー && 攻撃のクールダウンタイムが終わっていれば）
	if (player.IsPressed(PAD_INPUT_2)
		&& player.CanAttack())
	{
		return player.GetAttackState();
	}

	return nullptr;
}




unsigned int JumpState::GetBodyColor() const
{
	return GetColor(255, 220, 60);   // 黄
}

