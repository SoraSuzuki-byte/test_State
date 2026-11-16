/**
 * @file   Game.cpp
 *
 * @brief  ゲーム全体に関するソースファイル
 *
 * @author 鈴木蒼良
 *
 * @date   2026年10月12日
 */

// ヘッダファイルの読み込み ===================================================
#include "Game.h"
#include "Game/Screen.h"
#include "Game/Player/PlayerConstants.h"
#include "Game/Player/Player.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief デフォルトコンストラクタ
 *
 * @param なし
 */
Game::Game()
	: m_inputManager{}
	, m_gameContext	{ m_inputManager }
	, m_player		{ nullptr }
	, m_tentacle    { Vector2D(300.0f, 250.0f) }// 触手の付け根の位置
{
	// 乱数の初期値を設定
	SRand(static_cast<int>(time(nullptr)));
}



/**
 * @brief デストラクタ
 */
Game::~Game()
{

}



/**
 * @brief 初期化処理
 *
 * @param なし
 *
 * @return なし
 */
void Game::Initialize()
{
	// ゲームの初期化
	m_gameContext.inputManager.Initialize();

	m_player = std::make_unique<Player>();

	m_player->Initialize();

}



/**
 * @brief 更新処理
 *
 * @param 触手の付け根の位置
 *
 * @return なし
 */
void Game::Update(float elapsedTime)
{
	m_gameContext.inputManager.Update();

	// キー入力情報を取得する
	const int keyCondition = m_gameContext.inputManager.GetKeyCondition();
	const int keyTrigger = m_gameContext.inputManager.GetKeyTrigger();


	// Playerの攻撃が触手に当たるか
	if (m_player->CanDealAttackDamage()) // 攻撃判定を出せるなら
	{
		// 当たった節へダメージを与え、当たった節の個数を取得する
		const int hitCount = m_tentacle.TakeDamageByCircle(
			m_player->GetAttackCenter(),
			m_player->GetAttackRadius(),
			PlayerConstants::ATTACK_DAMAGE,
			m_player->GetAttackId());
	}





	// ゲームの更新
	m_player->Update(elapsedTime, keyCondition, keyTrigger);
	m_tentacle.Update(elapsedTime);
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Game::Render()
{
	// ゲームの描画

	// 地面
	DrawLine(0, static_cast<int>(PlayerConstants::GROUND_Y), 1280, static_cast<int>(PlayerConstants::GROUND_Y), GetColor(120, 120, 120));

	// プレイヤー
	m_player->Render();

	m_tentacle.Render();

	// 操作説明
	DrawString(10, 30, L"←→:移動  Z:ジャンプ  X:攻撃", GetColor(200, 200, 200));

	DrawFormatString(10, 60, GetColor(255, 255, 255),
		L"攻撃中:%d  ID:%d", m_player->IsAttacking(), m_player->GetAttackId());

}



/**
 * @brief 終了処理
 *
 * @param なし
 *
 * @return なし
 */
void Game::Finalize()
{
	// ゲームの終了処理
	m_player.reset();
}
