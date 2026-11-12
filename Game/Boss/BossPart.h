/**
 * @file   BossPart.h
 *
 * @brief  ボスの部位に関するヘッダファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月21日
 */
#pragma once
#include <memory>
#include "Library/GameMath.h"
#include "IBossPartObserver.h"
#include "BossPartState.h"
class BossPart
{
private:
	// 何番目の節か
	int m_index{};

	// 部位破壊などのイベントを通知するオブジェクト（通知先）
	IBossPartObserver* m_observer{ nullptr };

	// 現在のHP
	int m_hp{};
	// 最大HP（記録用）
	int m_maxHp{};

	// 中心座標
	Vector2D m_centerPosition{};

	// 半径
	float m_radius{};

	// 今のステート
	std::unique_ptr<BossPartState> m_state{};

	// ステートを変える
	void ChangeState(std::unique_ptr<BossPartState> nextState);
public:
	BossPart(const Vector2D& pos, float radius, int maxHp);
	//~BossPart();
	void Initialize();
	void Render()const;

	// 当たったかどうかの判定
	bool IsHit(const Vector2D& center, float radius) const;

	// ダメージを受け、HPが減る
	void TakeDamage(int damage);

	// HPが無いか？
	bool IsBroken() const;

	// 現在のHPを返す
	int GetHp() const;

	// 最大HPを取得する
	int GetMaxHp() const;

	// 位置を変える
	void SetPosition(const Vector2D& pos);

	// 部位破壊通知用のオブザーバーとパーツのインデックスを設定する
	void SetObserver(IBossPartObserver* observer, int index);

	// パーツが破壊されたことをオブザーバーに通知する
	void NotifyBroken();





	// パーツを強制的に破壊状態にする
	void ForceBreak();
};

