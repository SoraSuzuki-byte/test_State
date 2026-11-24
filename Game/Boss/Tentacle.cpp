/*
	@file   Tentacle.cpp
	@brief  触手クラスのソースファイル
	@author 鈴木蒼良
	@date   2026年11月4日
*/
#include "pch.h"
#include "Tentacle.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">付け根の位置</param> 
Tentacle::Tentacle(const Vector2D& root)
	: m_root { root }
{
	// 先に確保（途中で vector が再確保されてしまわないように）
	m_parts.reserve(SEGMENT_COUNT);
	

	for (int i = 0; i < SEGMENT_COUNT; i++)
	{
		// 付け根から右へ、一定の間隔で並べる
		Vector2D pos = m_root;
		pos.x += SEGMENT_LENGTH * i;

		// 根元から先端に向けて、だんだん細くする
		const float radius = BASE_RADIUS * (1.0f - 0.5f * static_cast<float>(i) / SEGMENT_COUNT);

		// その場で節を作る（BossPartはコピーできないため、emplace_back）
		m_parts.emplace_back(std::make_unique<BossPart>(pos, radius, PART_MAX_HP));
		m_parts.back()->SetObserver(this, i); // 「壊れた」の通知先は、この触手。と登録
		m_parts.back()->Initialize(); // HPは入っているので、状態（Normal）に入れる
	}
}

/// <summary>
/// デストラクタ
/// </summary>
Tentacle::~Tentacle()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">前フレームからの経過時間（秒）</param>
void Tentacle::Update(float elapsedTime)
{
	// 経過時間を蓄積
	m_time += elapsedTime;

	// 座標の初期値は付け根
	Vector2D currentPos = m_root;

	// 向きの角度は初期値
	float currentAngle = 0.0f;

	// 節ごとに計算して 位置を更新する
	for (int i = 0; i < SEGMENT_COUNT; i++)
	{
		// いまの位置を、この節に入れる
		m_parts[i]->SetPosition(currentPos);// 最初にこの行を実行することで、0番目の節（i = 0）の座標が確実に付け根の位置（m_root）に固定されます。

		// 角度を曲げる(節ごとに波をずらすので、波が付け根から先端へ伝わる)
		currentAngle += BEND + AMPLITUDE * std::sin(m_time * SPEED - i * PHASE);

		// 現在の節から見た『次の節が伸びている方向（進行方向）』に、1節ぶん進む
		currentPos.x += std::cos(currentAngle) * SEGMENT_LENGTH;
		currentPos.y += std::sin(currentAngle) * SEGMENT_LENGTH;
	}

	// 崩壊を始める
	UpdateCollapse(elapsedTime);

	// 一定時間ごとに、攻撃中と待機中を切り替える（仮の動き）
	m_attackModeTimer -= elapsedTime;
	if (m_attackModeTimer <= 0.0f)
	{
		m_isAttacking = !m_isAttacking;
		m_attackModeTimer += ATTACK_MODE_INTERVAL;   // 引き算ではなく足すと、時間のずれがたまらない
	}
}





/// <summary>
/// 描画
/// </summary>
void Tentacle::Render() const
{
// 先端から描くと、根元の円が手前に重なる
	for (int i = SEGMENT_COUNT - 1; i >= 0; i--)
	{
		m_parts[i]->Render();
	}

	// 攻撃中は、壊れていない節に赤い輪郭を付ける
	if (m_isAttacking)
	{
		for (const auto& part : m_parts)
		{
			if (part->IsBroken()) continue;

			const Vector2D c = part->GetCenter();
			DrawCircle(static_cast<int>(c.x),
				static_cast<int>(c.y),
				static_cast<int>(part->GetRadius()) + 2,
				GetColor(255, 60, 60),
				FALSE,
				3);   // 線の太さ
		}
	}
}





/// <summary>
/// 円と重なっている節にダメージを与える（当たった節の数字を返す）
/// </summary>
/// <param name="center">円の中心</param>
/// <param name="radius">円の半径</param>
/// <param name="damage">ダメージ量</param>
/// <returns></returns>
int Tentacle::TakeDamageByCircle(const Vector2D& center, float radius, int damage, int attackId)
{
	int hitCount = 0;

	for (int i = 0; i < SEGMENT_COUNT; i++)
		{
			if (m_parts[i]->IsHit(center, radius))
			{
				// 同じ攻撃ですでに当たった節ならfalse
				if (m_parts[i]->TakeDamageFromAttack(damage, attackId))
				{
					hitCount++;
				}
			}
		}

	return hitCount;
}





/// <summary>
/// index番目の節にダメージを与える
/// </summary>
/// <param name="index">節の番号</param>
/// <param name="damage">ダメージ量</param>
void Tentacle::TakeDamage(int index, int damage)
{
	// 範囲外の番号は無視する
	if (index < 0 || index >= SEGMENT_COUNT) return;

	m_parts[index]->TakeDamage(damage);
}





/// <summary>
/// 節が 壊れた時に呼ばれる（Observer）
/// </summary>
/// <param name="index">壊れた節の番号</param>
void Tentacle::OnPartBroken(int index)
{
	// 壊れた節より１つ先端側から 崩壊を始める
	const int next = index + 1;

	// もし先端が壊れたのであれば、崩れる節がない
	if (next >= SEGMENT_COUNT) return;

	// 崩壊していないか、より根元に近い節が壊れたなら、そこから崩壊をやり直す
	if (m_collapseIndex == -1 || next < m_collapseIndex)
	{
		m_collapseIndex = next;
		m_collapseTimer = COLLAPSE_INTERVAL;
	}
}





/// <summary>
/// 円（プレイヤ等）と触手の各節との当たり判定を行い、押し戻しベクトルを計算する
/// </summary>
/// <param name="center">円の中心座標</param>
/// <param name="radius">円の半径</param>
/// <param name="pushOut">円を押し出すベクトル</param>
/// <returns>いずれかの節と重なっているか</returns>
bool Tentacle::IsCollidingWithCircle(const Vector2D& center, float radius, Vector2D& pushOut) const
{
	pushOut.x = 0.0f;
	pushOut.y = 0.0f;

	// そもそも、触手全体を囲む 大きな円と重なっていなければ早期リターン
	const float dx = center.x - m_root.x;
	const float dy = center.y - m_root.y;
	const float reach = REACH + radius;
	if ((dx * dx) + (dy * dy) > (reach * reach)) return false;

#pragma region 各節を調べて最も深くめり込んでいる押し出しを 採用する
	bool isHit = false;
	float maxDepthSq = 0.0f;

	for (int i = 0; i < SEGMENT_COUNT; i++)
	{
		Vector2D push;
		//　当たっていなければ、スキップ
		if (!m_parts[i]->CalcPushOut(center, radius, push)) continue;

		isHit = true;
		// 同じ向きの押し出しが重なっても2倍にならないよう、絶対値が大きい方を採用する
		if (std::abs(push.x) > std::abs(pushOut.x)) {
			pushOut.x = push.x;
		};
		if (std::abs(push.y) > std::abs(pushOut.y)) {
			pushOut.y = push.y;
		};
	}
#pragma endregion

	return isHit;
}





/// <summary>
/// 崩壊を進める
/// </summary>
/// <param name="elapsedTime">前フレームからの経過時間（秒）</param>
void Tentacle::UpdateCollapse(float elapsedTime)
{
	// 崩壊していないなら何もしない
	if (m_collapseIndex == -1) return;

	// 次の節を壊すまで待つ
	m_collapseTimer -= elapsedTime;
	if (m_collapseTimer > 0.0f) return;// 0より大きければ以下をスキップ

	// 1節 壊して、次の節へ進む
	// （壊れた節の通知で OnPartBroken が呼ばれるが、先端側であるため、m_collapseIndex は変わらない）
	m_parts[m_collapseIndex]->ForceBreak();
	m_collapseIndex++;
	m_collapseTimer = COLLAPSE_INTERVAL;

	// 先端まで壊し終えたら、崩壊を終わる
	if (m_collapseIndex >= SEGMENT_COUNT)
	{
		m_collapseIndex = -1;
	}
}