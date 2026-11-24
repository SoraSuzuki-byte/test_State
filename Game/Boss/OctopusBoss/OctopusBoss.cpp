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

	// 最初は登場（Enter）のスタート位置（画面外）に置いておく
	tentacle->SetRootOffset(Vector2D{ OFFSCREEN_DISTANCE, 0.0f });

	// すべての設定が終わった最後の1行で std::move を呼ぶのが鉄則
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
	// 行動段階の更新
	UpdateStage(elapsedTime);

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

	if (m_stage == Stage::Chance)
	{
		DrawString(580, 100, L"CHANCE!", GetColor(255, 255, 0));
	}
}





/// <summary>
/// 円との当たり判定を行い、押し出し量を計算する
/// </summary>
/// <param name="center">円の中心座標</param>
/// <param name="radius">円の半径</param>
/// <param name="pushOut">一番大きくめり込んだ部位からの押し出しベクトル（出力）</param>
/// <returns>いずれかの触手と当たっていれば true</returns>
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
	return m_stage == Stage::Attack;
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





/// <summary>
/// 行動段階（登場→攻撃→チャンス→退場）のタイマー更新と切り替え
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void OctopusBoss::UpdateStage(float elapsedTime)
{
	m_stageTimer -= elapsedTime;
	if (m_stageTimer <= 0.0f)
	{
		switch (m_stage)
		{
			case Stage::Enter:
			{
				m_stage = Stage::Attack;
				m_stageTimer = ATTACK_TIME;  
				for (auto& tentacle : m_tentacles) { tentacle->SetAttacking(true); }
				break;
			}
			case Stage::Attack:
			{
				m_stage = Stage::Chance;
				m_stageTimer = CHANCE_TIME;
				for (auto& tentacle : m_tentacles) { tentacle->SetAttacking(false); }
				break;
			}
			case Stage::Chance:
			{
				m_stage = Stage::Retreat;
				m_stageTimer = RETREAT_TIME;
				break;
			}
			case Stage::Retreat:
			{
				// 画面の外にいるうちに、壊れた節を元に戻す
				for (auto& tentacle : m_tentacles) { tentacle->Restore(); }
				m_stage = Stage::Enter; m_stageTimer = ENTER_TIME;
				break;
			}
			//default :
			//{

			//}
		}
	}

	// 現在の段階に合わせて、付け根のずらし量（オフセット）を決める
	Vector2D offset{ 0.0f, 0.0f };
	if (m_stage == Stage::Enter)
	{
		// 1.0 → 0.0 へ減っていく（右の画面外から定位置へ入ってくる）
		const float t = m_stageTimer / ENTER_TIME;
		offset.x = OFFSCREEN_DISTANCE * t;
	}
	else if (m_stage == Stage::Retreat)
	{
		// 0.0 → 1.0 へ増えていく（定位置から右の画面外へ出ていく）
		const float t = 1.0f - (m_stageTimer / RETREAT_TIME);
		offset.x = OFFSCREEN_DISTANCE * t;
	}

	for (auto& tentacle : m_tentacles)
	{
		tentacle->SetRootOffset(offset);
	}
}