/**
 * @file   PartBrokenState.cpp
 *
 * @brief  ボスのPartBrokenStateのソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月11日
 */
#include "pch.h"
#include "PartBrokenState.h"
#include "Game/Boss/BossPart.h"

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