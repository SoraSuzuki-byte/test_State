/**
 * @file   BossPartState.cpp
 *
 * @brief  ボスの状態（Stateパターン）に関するソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月21日
 */
#include "pch.h"
#include "BossPartState.h"
#include "BossPart.h"

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



// ===========================================================================
// PartBrokenState（HPが0）
// ===========================================================================
std::unique_ptr<BossPartState> PartBrokenState::OnDamaged(BossPart& bossPart)
{
	UNREFERENCED_PARAMETER(bossPart); // 使わない引数であるとコンパイラに伝える

	// 壊れた後は、二度と状態が変わらない
	return nullptr;
}

unsigned int PartBrokenState::GetBodyColor() const
{
	return Colors::GRAY;
}

/// <summary>
/// この状態に遷移したときの初期化処理を行なう
/// </summary>
/// <param name="bossPart">対象となるボスの部位</param>
void PartBrokenState::Enter(BossPart& bossPart)
{
	bossPart.NotifyBroken(); // 壊れた瞬間に 通知先へ知らせる
}
