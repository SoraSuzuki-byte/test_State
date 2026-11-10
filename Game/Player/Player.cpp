/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーに関するソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// ヘッダファイルの読み込み ===================================================
#include "Player.h"

#include "Game/Screen.h"
#include "PlayerConstants.h"



// メンバ関数の定義 ===========================================================
/**
 * @brief デフォルトコンストラクタ
 */
Player::Player()
	: m_x{ 100.0f }
	, m_y{ PlayerConstants::GROUND_Y }
	, m_velocityY{ 0.0f }
	, m_facingRight{ true }
	, m_keyCondition{ 0 }
	, m_keyTrigger{ 0 }
	, m_state{ nullptr }
{
	// 最初は待機状態
	ChangeState(&m_idle);
}



/**
 * @brief デストラクタ
 */
Player::~Player()
{

}



/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime 前フレームからの経過時間（秒）
 * @param[in] keyCondition 現在のキー情報（押している間）
 * @param[in] keyTrigger   押された瞬間のキー情報
 *
 * @return なし
 */
void Player::Update(float elapsedTime, int keyCondition, int keyTrigger)
{
	m_keyCondition = keyCondition;
	m_keyTrigger = keyTrigger;

	// クールダウンの処理
	if (m_attackCooldown > 0.0f) {
		m_attackCooldown-= elapsedTime;

		if (m_attackCooldown < 0.0f) {
			m_attackCooldown = 0.0f;
		}
	}
		

	// 現在の状態に処理を任せ、遷移先があれば切り替える
	PlayerState* nextState = m_state->Update(*this, elapsedTime);
	if (nextState)
	{
		ChangeState(nextState);
	}
}




/**
 * @brief 描画処理
 */
void Player::Render() const
{
	const int left   = static_cast<int>(m_x);
	const int top    = static_cast<int>(m_y - PlayerConstants::HEIGHT);
	const int right  = static_cast<int>(m_x + PlayerConstants::WIDTH);
	const int bottom = static_cast<int>(m_y);

	// 本体（状態ごとの色）
	DrawBox(left, top, right, bottom, m_state->GetBodyColor(), TRUE);

	// 向きがわかる「目」
	int eyeX = left + 4;        // 左向きのときの位置
	if (m_facingRight)
	{
		eyeX = right - 12;      // 右向きのときの位置
	}
	DrawBox(eyeX, top + 10, eyeX + 8, top + 18, GetColor(255, 255, 255), TRUE);

	// 状態固有の描画（攻撃の判定など）
	m_state->RenderEffect(*this);

	// デバッグ表示
	DrawString(10, 10, L"State:", GetColor(255, 255, 255));
	DrawString(70, 10, m_state->GetName(), GetColor(255, 255, 255));
}



/**
 * @brief 状態の変更
 *
 * @param[in] nextState 次の状態
 */
void Player::ChangeState(PlayerState* nextState)
{
	if (m_state) // nullptrじゃなければ
	{
		m_state->Exit(*this);		// ①終了処理を呼ぶ
	}

	m_state = nextState;			// ②ポインタの代入

	m_state->Enter(*this);			// ③新しいStateの開始処理を呼ぶ
}



/**
 * @brief X方向に移動（画面外に出ないよう制限する）
 *
 * @param[in] dx 移動量
 */
void Player::MoveX(float dx)
{
	int screenW = 0;
	int screenH = 0;
	GetDrawScreenSize(&screenW, &screenH);

	m_x += dx;

	if (m_x < 0.0f)
	{
		m_x = 0.0f;
	}
	if (m_x > static_cast<float>(screenW) - PlayerConstants::WIDTH)
	{
		m_x = static_cast<float>(screenW) - PlayerConstants::WIDTH;
	}
}



/**
 * @brief ボタンが押されているか
 */
bool Player::IsHeld(int button) const
{
	return (m_keyCondition & button) != 0;
}



/**
 * @brief ボタンが押された瞬間か
 */
bool Player::IsPressed(int button) const
{
	return (m_keyTrigger & button) != 0;
}



/**
 * @brief 左右入力（左:-1, なし:0, 右:1）
 */
int Player::GetMoveDirection() const
{
	int direction = 0;

	if (IsHeld(PAD_INPUT_RIGHT)) { direction += 1; }
	if (IsHeld(PAD_INPUT_LEFT))  { direction -= 1; }

	return direction;
}

/// <summary>
/// 攻撃できるかを返す
/// </summary>
/// <returns>攻撃可能か</returns>
bool Player::CanAttack() const
{
	return m_attackCooldown <= 0.0f;
}


/// <summary>
/// クールダウンタイムのセット
/// </summary>
void Player::StartAttackCooldown()
{
	m_attackCooldown = PlayerConstants::ATTACK_COOLDOWN;
}
