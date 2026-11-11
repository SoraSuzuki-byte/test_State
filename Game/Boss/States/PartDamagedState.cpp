/**
 * @file   PartDamagedState.cpp
 *
 * @brief  ボスのPartDamagedStateのソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月11日
 */
#include "pch.h"
#include "PartDamagedState.h"
#include "Game/Boss/BossPart.h"
#include "Game/Boss/States/PartBrokenState.h"


 // ===========================================================================
 // PartDamagedState（HPが半分以下）
 // ===========================================================================
std::unique_ptr<BossPartState> PartDamagedState::OnDamaged(BossPart& bossPart)
{
	// 0以下になったら、Brokenへ
	if (bossPart.GetHp() <= 0)
	{
		return std::make_unique<PartBrokenState>();
	}

	return nullptr;
}

unsigned int PartDamagedState::GetBodyColor() const
{
	return Colors::YELLOW;
}

