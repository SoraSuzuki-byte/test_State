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
#include "Game/Boss/States/PartNormalState.h"
#include "Game/Boss/States/PartDamagedState.h"
#include "Game/Boss/States/PartBrokenState.h"

class BossPart
{
private:
	// 通常のステート
	PartNormalState m_normalState;

	// HPが半分以下のステート
	PartDamagedState m_damagedState;

	// 壊れたステート
	PartBrokenState m_brokenState;

	// 今のステート
	BossPartState*    m_state       {nullptr};


	// 部位破壊などのイベントを通知するオブジェクト（通知先）
	IBossPartObserver* m_observer{ nullptr };

	// 何番目の節か
	int m_index{};

	// 現在のHP
	int m_hp{};

	// 最大HP（記録用）
	int m_maxHp{};

	// 中心座標
	Vector2D m_centerPosition{};

	// 半径
	float m_radius{};



	// 最後にダメージを受けた攻撃の番号（0 は「まだなし」）
	int m_lastAttackId{};

public:
	BossPart(const Vector2D& pos, float radius, int maxHp);
	//~BossPart();

	// 自分のメンバを指すポインタを持つため、コピーとムーブを禁止する
	BossPart(const BossPart&) = delete;
	BossPart& operator=(const BossPart&) = delete;
	BossPart(BossPart&&) = delete;
	BossPart& operator=(BossPart&&) = delete;

	// 初期化・描画
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

	// 節の描画に使う
	Vector2D GetCenter() const { return m_centerPosition; }
	float GetRadius() const { return m_radius; }

	// Stateの取得
	PartNormalState* GetPartNormalState() { return &m_normalState; }
	PartDamagedState* GetPartDamagedState(){ return &m_damagedState; }
	PartBrokenState* GetPartBrokenState(){ return &m_brokenState; }

	// 位置を変える
	void SetPosition(const Vector2D& pos);

	// 部位破壊通知用のオブザーバーとパーツのインデックスを設定する
	void SetObserver(IBossPartObserver* observer, int index);

	// パーツが破壊されたことをオブザーバーに通知する
	void NotifyBroken();

	// パーツを強制的に破壊状態にする
	void ForceBreak();

	/// <summary>
	/// 攻撃IDを確認し、未ヒットの攻撃であればダメージを受ける
	/// </summary>
	/// <param name="damage">受けるダメージ量</param>
	/// <param name="attackId">攻撃の識別番号（多段ヒット防止用）</param>
	/// <returns>ダメージを受けた場合はtrue、すでにヒット済みの場合はfalse</returns>
	bool TakeDamageFromAttack(int damage, int attackId);

	/// <summary>
	/// 円と重なっているか判定し、重なっていれば押し戻すベクトルを計算して処理もする
	/// </summary>
	/// <param name="center">円の中心</param>
	/// <param name="radius">円の半径</param>
	/// <param name="pushOut">円を押し出すベクトル（出力用）</param>
	/// <returns>円と重なっているかどうか</returns>
	bool CalcPushOut(const Vector2D& center, float radius, Vector2D& pushOut) const;



// 内部処理
private:
	/// <summary>
	/// ステートを変更
	/// </summary>
	void ChangeState(BossPartState* nextState);

};

