/**
 * @file   PartNormalState.cpp
 *
 * @brief  ボスのPartNormalStateのソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月11日
 */
#include "pch.h"
#include "PartNormalState.h"
#include "Game/Boss/BossPart.h"
#include "PartDamagedState.h"
#include "PartBrokenState.h"


 // ===========================================================================
 // PartNormalState（HPが半分より多い）
 // ===========================================================================
/// <summary>
/// ダメージを受けた後の状態判定
/// </summary>
/// <returns>遷移先の状態（遷移しないなら nullptr）</returns>
std::unique_ptr<BossPartState> PartNormalState::OnDamaged(BossPart& bossPart)
{
	// 先ず「壊れたか」を確認する（一撃で壊れる場合があるため）
	if (bossPart.GetHp() <= 0)
	{
		return std::make_unique<PartBrokenState>();
	}

	// HPが半分以下になったら Damaged へ（掛け算にすると float が要らない）	// 両辺を 2 倍しても不等式の意味は変わらない！
																			//  HP <= MaxHP / 2  ⟺  HP * 2 <= MaxHP
	if (bossPart.GetHp() * 2 <= bossPart.GetMaxHp())
	{
		return std::make_unique<PartDamagedState>();
	}

	return nullptr;
}

unsigned int PartNormalState::GetBodyColor() const
{
	return Colors::GREEN;
}