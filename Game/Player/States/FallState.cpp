/**
 * @file   FallState.cpp
 *
 * @brief  プレイヤーのFall状態のソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月10日
 */
#include "pch.h"
#include "Game/Player/PlayerConstants.h"
#include "FallState.h"
#include "Game/Player/Player.h"
#include "IdleState.h"
#include "RunState.h"



 // ===========================================================================
 // FallState（落下）
 // ===========================================================================




/// <summary>
/// 更新
/// </summary>
/// <param name="player">Playerの参照</param>
/// <param name="elapsedTime">経過時間</param>
/// <returns>切り替わるState</returns>
PlayerState* FallState::Update(Player& player, float elapsedTime)
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




unsigned int FallState::GetBodyColor() const
{
	return GetColor(255, 140, 0);   // オレンジ（橙）
}

