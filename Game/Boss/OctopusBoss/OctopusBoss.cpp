/**
 * @file   OctopusBoss.cpp
 *
 * @brief タコ型ボスのクラス
 *
 * @author 鈴木蒼良
 *
 * @date   2026年11月24日
 */

#include "pch.h"
#include "OctopusBoss.h"
#include "Tentacle.h"

/// <summary>
/// コンストラクタ
/// </summary>
OctopusBoss::OctopusBoss()
	: Boss{ MAX_HP }
{
	// 触手を1本生成して登録
	//auto tentacle = std::make_unique<Tentacle>(/* 付け根の座標など */);
	auto tentacle = std::make_unique<Tentacle>(Vector2D(600.0f, 250.0f));

	// 触手に「壊れたら自分(this)に連絡してね」と登録する
	tentacle->SetObserver(this);

	m_tentacles.push_back(std::move(tentacle));
}





// unique_ptr<Tentacle> を正しく破棄するため .cpp 側に書く
OctopusBoss::~OctopusBoss() = default;





/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void OctopusBoss::Update(float elapsedTime)
{
	for (auto& tentacle : m_tentacles)
	{
		tentacle->Update(elapsedTime);
	}
}






/// <summary>
/// 描画
/// </summary>
void OctopusBoss::Render() const
{
	for (const auto& tentacle : m_tentacles)
	{
		tentacle->Render();
	}
}





/// <summary>
/// 
/// </summary>
/// <param name="center"></param>
/// <param name="radius"></param>
/// <param name="pushOut"></param>
/// <returns></returns>
bool OctopusBoss::IsCollidingWithCircle(const Vector2D& center, float radius, Vector2D& pushOut) const
{
	bool isHit = false;
	Vector2D maxPushOut{ 0.0f, 0.0f };
	float maxLenSq = 0.0f;

	for (const auto& tentacle : m_tentacles)
	{
		Vector2D tempPushOut{ 0.0f, 0.0f };
		if (tentacle->IsCollidingWithCircle(center, radius, tempPushOut))
		{
			isHit = true;
			// 一番大きくめり込んだ押し出し量を採用する
			const float lenSq = tempPushOut.x * tempPushOut.x + tempPushOut.y * tempPushOut.y;
			if (lenSq > maxLenSq)
			{
				maxLenSq = lenSq;
				maxPushOut = tempPushOut;
			}
		}
	}

	if (isHit)
	{
		pushOut = maxPushOut;
	}
	return isHit;
}





/// <summary>
/// いま、触れたらダメージを与える状態か
/// </summary>
/// <returns>触れたらダメージを与える状態か</returns>
bool OctopusBoss::IsAttacking() const
{
	for (const auto& tentacle : m_tentacles)
	{
		if (tentacle->IsAttacking())
		{
			return true;
		}
	}
	return false;
}





/// <summary>
/// プレイヤーの攻撃を受ける（当たった部位の個数を返す）
/// </summary>
/// <param name="center">円の中心</param>
/// <param name="radius">円の半径</param>
/// <param name="damage">ダメージ量</param>
/// <returns></returns>
int OctopusBoss::TakeDamageByCircle(const Vector2D& center, float radius, int damage, int attackId)
{
	int totalHitCount = 0;
	for (auto& tentacle : m_tentacles)
	{
		totalHitCount += tentacle->TakeDamageByCircle(center, radius, damage, attackId);
	}
	return totalHitCount;
}





/// <summary>
/// 部位が1つ壊れたときに呼ばれる
/// </summary>
void OctopusBoss::OnSegmentBroken()
{
	// 触手の部位が1つ壊れるたびにボスのHPを減らす
	ReduceHp(DAMAGE_PER_SEGMENT);
}