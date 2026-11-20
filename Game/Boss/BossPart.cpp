/**
 * @file   BossPart.cpp
 *
 * @brief  ボスの部位に関するソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月21日
 */
#include "pch.h"
#include "BossPart.h"


/// <summary>
/// コンストラクタ
/// </summary>
BossPart::BossPart(const Vector2D& pos, float radius, int maxHp)
	: m_hp             { maxHp }
	, m_maxHp          { maxHp }
	, m_centerPosition {pos}
	, m_radius         {radius}
{
}

/// <summary>
/// 初期化処理
/// </summary>
void BossPart::Initialize()
{
	ChangeState(&m_normalState);
}

/// <summary>
/// 描画処理
/// </summary>
void BossPart::Render() const
{
	DrawCircle(
		static_cast<int>(m_centerPosition.x),
		static_cast<int>(m_centerPosition.y),
		static_cast<int>(m_radius),
		m_state->GetBodyColor(),
		TRUE
	);
	
	DrawFormatString(
static_cast<int>(m_centerPosition.x),
		static_cast<int>(m_centerPosition.y),
		GetColor(0, 0, 0),
		L"HP: %d / %d", m_hp, m_maxHp);
}




/// <summary>
/// 当たったかどうかの判定
/// </summary>
/// <param name="center">中心</param>
/// <param name="radius">半径</param>
/// <returns>当たったか</returns>
bool BossPart::IsHit(const Vector2D& center, float radius) const
{
	if (IsBroken()) return false; // 壊れた節には当たらない

	const float dx = m_centerPosition.x - center.x;
	const float dy = m_centerPosition.y - center.y;
	const float r = m_radius + radius;

	return (dx * dx + dy * dy) <= (r * r);
}




/// <summary>
/// ダメージを受け、HPが減る
/// </summary>
void BossPart::TakeDamage(int damage)
{
	if (IsBroken()) return; // 壊れていたらスキップする

	m_hp -= damage;
	if (m_hp < 0) m_hp = 0; // HPを0以下にしない

	// 現在の状態に「ダメージを受けた」と伝え、遷移先があれば切り替える
	BossPartState* nextState = m_state->OnDamaged(*this);
	if (nextState != nullptr)
	{
		ChangeState(nextState);
	}
}




/// <summary>
/// HPが無いか？
/// </summary>
/// <returns>HPが無くて壊れているか</returns>
bool BossPart::IsBroken() const
{
	return m_hp <= 0; // 真偽を 返している
}




/// <summary>
/// 現在のHPを返す
/// </summary>
/// <returns>現在のHP</returns>
int BossPart::GetHp() const
{
	return m_hp;
}




// <summary>
/// 最大HPを返す
/// </summary>
int BossPart::GetMaxHp() const
{
	return m_maxHp;
}




/// <summary>
/// 位置を変える
/// </summary>
/// <param name="pos">変えたい位置の値</param>
void BossPart::SetPosition(const Vector2D& pos)
{
	m_centerPosition = pos;
}




/// <summary>
/// 部位破壊通知用のオブザーバーとパーツのインデックスを設定する
/// </summary>
/// <param name="observer">通知先となるオブザーバーのポインタ</param>
/// <param name="index">このパーツの識別インデックス</param>
void BossPart::SetObserver(IBossPartObserver* observer, int index)
{
	m_observer = observer;
	m_index = index;
}




/// <summary>
	/// パーツが破壊されたことをオブザーバーに通知する
	/// </summary>
void BossPart::NotifyBroken()
{
	// オブザーバー（通知先）が設定されている場合のみ通知する
	if (m_observer != nullptr)
	{
		m_observer->OnPartBroken(m_index);
	}
}




/// <summary>
/// パーツを強制的に破壊状態にする
/// </summary>
void BossPart::ForceBreak()
{
	if (IsBroken()) return;   // すでに壊れていたら何もしない

	m_hp = 0;
	ChangeState(&m_brokenState);
}





/// <summary>
/// 攻撃IDを確認し、未ヒットの攻撃であればダメージを受ける
/// </summary>
/// <param name="damage">受けるダメージ量</param>
/// <param name="attackId">攻撃の識別番号（多段ヒット防止用）</param>
/// <returns>ダメージを受けた場合はtrue、すでにヒット済みの場合はfalse</returns>
bool BossPart::TakeDamageFromAttack(int damage, int attackId)
{
	// この攻撃では、すでにダメージを受けている
	if (attackId == m_lastAttackId) return false;

	m_lastAttackId = attackId;
	TakeDamage(damage);
	return true;
}





/// <summary>
/// ステートを変更
/// </summary>
void BossPart::ChangeState(BossPartState* nextState)
{
	if (m_state)
	{
		m_state->Exit(*this);   // 古い状態の終了処理
	}

	m_state = nextState; // ポインタを切り替える
	m_state->Enter(*this); // 新しい状態の開始処理
}
