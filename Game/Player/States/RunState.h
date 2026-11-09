/**
 * @file   RunState.h
 *
 * @brief  プレイヤーのRun状態のヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月5日
 */
#pragma once
 /**
  * @brief 走り（緑）
  */
#include "Game/Player/PlayerState.h"// 基底クラスを継承するので必須
class Player;


class RunState : public PlayerState
{
public:
	PlayerState* Update(Player& player, float elapsedTime) override;
	unsigned int GetBodyColor() const override;
	const wchar_t* GetName() const override { return L"Run"; }
};


