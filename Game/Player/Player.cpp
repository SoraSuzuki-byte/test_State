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




/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
}




/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}




/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	m_x = 100.0f;
	m_y = PlayerConstants::GROUND_Y;

	// 最初は IdleState
	ChangeState(&m_idle);
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

	// 重力の更新
	if (!IsGrounded())
	{
		// 重力の適応
		ApplyGravity(elapsedTime);
	}

	// 位置の更新
	UpdatePosition(elapsedTime);

	// 着地補正の処理
	if (IsGrounded() && IsFalling())
	{
		SetY(PlayerConstants::GROUND_Y);
		SetVelocityY(0.0f);
	}
}




/// <summary>
/// 描画
/// </summary>
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
	DrawFormatString(10, 50, GetColor(255, 255, 255), L"VelX: %.1f", m_velocityX);
	DrawFormatString(10, 100, GetColor(255, 255, 255), L"VelY: %.1f", m_velocityY);
}




/// <summary>
/// Stateの変更
/// </summary>
/// <param name="nextState">次のState</param>
void Player::ChangeState(PlayerState* nextState)
{
	if (m_state) // nullptrじゃなければ
	{
		m_state->Exit(*this);		// ①終了処理を呼ぶ
	}

	m_state = nextState;			// ②ポインタの代入

	m_state->Enter(*this);			// ③新しいStateの開始処理を呼ぶ
}




/// <summary>
/// X方向に移動（画面外に出ないよう制限する）
/// </summary>
/// <param name="dx">移動量</param>
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




/// <summary>
/// ボタンが押されているか
/// </summary>
/// <param name="button">押されたボタン</param>
/// <returns>押されたボタンを返す</returns>
bool Player::IsHeld(int button) const
{
	return (m_keyCondition & button) != 0;
}




/// <summary>
/// ボタンが押された"瞬間"か
/// </summary>
/// <param name="button">押されたボタン</param>
/// <returns>押されたボタンを返す</returns>
bool Player::IsPressed(int button) const
{
	return (m_keyTrigger & button) != 0;
}




/// <summary>
/// 左右入力（左:-1, なし:0, 右:1）
/// </summary>
/// <returns>X軸の移動量</returns>
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



/// <summary>
/// 位置の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Player::UpdatePosition(float elapsedTime)
{
	// X座標の更新
	MoveX(m_velocityX * elapsedTime);

	// Y座標の更新
	m_y += m_velocityY * elapsedTime;
}



/// <summary>
/// 重力の適応
/// </summary>
void Player::ApplyGravity(float elapsedTime)
{
	SetVelocityY(GetVelocityY() + PlayerConstants::GRAVITY * elapsedTime);
}




/// <summary>
/// 着地しているかどうか を返す
/// </summary>
/// <returns>着地しているか</returns>
bool Player::IsGrounded() const
{
	 return (GetY() >= PlayerConstants::GROUND_Y);
}
