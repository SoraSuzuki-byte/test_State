/**
 * @file   PlayerState.cpp
 *
 * @brief  プレイヤーの状態（Stateパターン）に関するソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// ヘッダファイルの読み込み ===================================================
#include "PlayerState.h"

#include "Game/Screen.h"
#include "Player.h"
#include "PlayerConstants.h"
#include "Game/Player/States/IdleState.h"
#include "Game/Player/States/RunState.h"




// 定数の定義 =================================================================
namespace
{
}









// ===========================================================================
// JumpState（ジャンプ）
// ===========================================================================
void JumpState::Enter(Player& player)
{
	// 上向きの初速を与える
	player.SetVelocityY(PlayerConstants::JUMP_SPEED);
}

std::unique_ptr<PlayerState> JumpState::Update(Player& player, float elapsedTime)
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
			return std::make_unique<RunState>();
		}
		return std::make_unique<IdleState>();
	}

	return nullptr;
}

unsigned int JumpState::GetBodyColor() const
{
	return GetColor(255, 220, 60);   // 黄
}



// ===========================================================================
// AttackState（攻撃）
// ===========================================================================
void AttackState::Enter(Player& player)
{
	UNREFERENCED_PARAMETER(player);
	m_timer = PlayerConstants::ATTACK_TIME;
}

std::unique_ptr<PlayerState> AttackState::Update(Player& player, float elapsedTime)
{
	UNREFERENCED_PARAMETER(player);

	// 持続時間が終わったら待機へ
	m_timer -= elapsedTime;
	if (m_timer <= 0.0f)
	{
		return std::make_unique<IdleState>();
	}

	return nullptr;
}

void AttackState::RenderEffect(const Player& player) const
{
	// 攻撃判定の見た目（向いている方向に箱を出す）
	const int attackW = 30;
	const int attackH = 20;

	const int top = static_cast<int>(player.GetY() - PlayerConstants::HEIGHT) + 15;

	int left = static_cast<int>(player.GetX()) - attackW;   // 左向きのときの位置
	if (player.IsFacingRight())
	{
		left = static_cast<int>(player.GetX() + PlayerConstants::WIDTH);   // 右向きのときの位置
	}

	DrawBox(left, top, left + attackW, top + attackH, GetColor(255, 180, 180), TRUE);
}

unsigned int AttackState::GetBodyColor() const
{
	return GetColor(255, 90, 90);   // 赤
}
