#include "Player.h"
#include <DxLib.h>
#include "../../../MyLib/Input/Input.h"
#include "../../../MyLib/Sound/Sound.h"

const char HAND_PATH[] = { "data/Game/Stage1/anim1.png" };
const char RESPAWN_PATH[] = { "data/Game/Stage1/Dead.png" };
//ジャンプ時間
const float JUMP_TIME = 12.f;
//ジャンプ高さ 
const int JUMP_HIGH = 15;
//プレイヤースピード
const int PLAYER_SPEED = 5;
//プレイヤーが後方に飛ぶ速度
const int PLAYER_PUSH = 2;
//プレイヤー復活数
const int PLAYER_RESPAWN = 3;

//初期化
void CPlayer::Init()
{
	// キャラクターの初期データをセット
	PlayerX = 1820;
	PlayerY = 800;

	JumpPower = 0.f;
	time = JUMP_TIME;
	life = true;
	BrockHit = false;
	Respawn = PLAYER_RESPAWN;
	Clear = false;
	Gameover = false;
	Deadpath = -1;
	RespawnTime = 0;

	//文字の大きさ変更
	SetFontSize(80);
}
//ロード
void CPlayer::Load()
{
	// グラフィックのロード
	LoadDivGraph(HAND_PATH, MaxFrame, MaxFrame, 1, 128, 128, Ani_image);
	//LoadDivGraph("画像ファイルのパス", MaxFrame, MaxFrame, 1, 196, 245, Ani_image)
	Deadpath = LoadGraph(RESPAWN_PATH, true);
}
//ステップ
void CPlayer::Step()
{
	//ジャンプ処理
	if (life == true)
		Jump();
	else
		RespawnTime++;
	
	//吹き飛ばされているときは移動できない
	if (BrockHit == false )
	{
		if (life == true)
		{
			if (CheckHitKey(KEY_INPUT_D) == 1)
				PlayerX += PLAYER_SPEED;	// 右を押していたら右に進む
			if (CheckHitKey(KEY_INPUT_A) == 1)
				PlayerX -= PLAYER_SPEED;	// 左を押していたら左に進む
		}
	}
	if (CInput::IsInputPush(CInput::INPUT_RESPAWN) && !life)
	{
		if (RespawnTime > 120)
		{
			Respawn -= 1;
			life = true;	//リスポーン
			RespawnTime = 0;
		}
	}
	
	//画面外にいかないようにする処理
	if (PlayerX < 0)
		PlayerX = 0;
	if (PlayerX >= 1792)
		PlayerX = 1792;

}
//描画
void CPlayer::Draw()
{
	// プレイヤーを描画する
	if (life == true)
	{  //画像の表示
		if (Frame_adjust == 5) {
			Frame++;
			Frame_adjust = 0;
		}
		if (Frame == MaxFrame - 1) {
			Frame = 0;
		}
		Frame_adjust++;
		DrawGraph(PlayerX, PlayerY, Ani_image[Frame], true);
	}	
	else
	{
		DrawFormatString(500, 40, GetColor(255, 99, 71), "[R]でリスポーン");
		//死んだ位置描画
		DrawRotaGraph(PlayerX, PlayerY, 1.f, 1.f,Deadpath,true, false);
	}
	//残機表示
	DrawFormatString(20, 40, GetColor(51, 156, 255), "残機：%d", Respawn);
}
//破棄
void CPlayer::Exit()
{
	DeleteGraph(PlayerGraph);
}

//HIT処理
void CPlayer::Hit()
{
	if(life == true)
	life = false;

	//ゲームオーバーへ
	if (Respawn == 0)
		Gameover = true;
}
//ジャンプ
void CPlayer::Jump()
{
	// 自動で上に進む
	if (time == 0.0f)
	{
		PlayerY -= JUMP_HIGH;
	}

	time = JUMP_TIME;		

	// 落下処理
	PlayerY -= (int)JumpPower;
	// 落下加速度を加える
	JumpPower -= 0.3f;

	// もし地面についていたらリセット
	if (PlayerY > 720)
	{
		PlayerY = 720;
		JumpPower = 0;
		BrockHit = false;
	}
	for (int i = 0; i < 5; i++)
		time = time - 5.f;

	if (time < 0.0f)
		time = 0.0f;

	//空中ブロックに当たれば後方に吹き飛ぶ
	if (BrockHit == true)
		PlayerX += PLAYER_PUSH;
	else
		PlayerX += 1;

}



