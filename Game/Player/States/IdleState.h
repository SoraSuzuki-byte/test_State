/**
 * @file   IdleState.h
 *
 * @brief  プレイヤーのIdle状態のヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#pragma once
#include "Game/Player/States/PlayerState.h"// 基底クラスを継承するので必須
class Player;


 /**
  * @brief 待機（青）
  */
class IdleState : public PlayerState
{
public:
	void Enter(Player& player) override;
	PlayerState* Update(Player& player, float elapsedTime) override;
	//unsignedは、「負の数を扱わない」
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Idle"; }
};


