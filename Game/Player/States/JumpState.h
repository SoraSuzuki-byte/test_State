/**
 * @file   JumpState.h
 *
 * @brief  プレイヤーのJump状態のヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#pragma once
#include "Game/Player/PlayerState.h"// 基底クラスを継承するので必須
class Player;

 /**
  * @brief ジャンプ（黄）
  */
class JumpState : public PlayerState
{
public:
	void Enter(Player& player) override;
	PlayerState* Update(Player& player, float elapsedTime) override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Jump"; }
};


