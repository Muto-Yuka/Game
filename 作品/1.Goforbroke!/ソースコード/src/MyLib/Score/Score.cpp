#include<DxLib.h>
#include "Score.h"

static const int NUMBER = 10;			//読み込む画像数「０」～「９」
static const int NUMBER_SIZE_X = 16;	//数字サイズ横(画像サイズ)
static const int NUMBER_SIZE_Y = 32;	//数字サイズ縦(画像サイズ)
static const int DIGIT_NUMBER = 3;		//表示可能な桁数
static const int START_POS_X = 580;		//スコア表示開始位置　横（どこに表示するか）
static const int START_POS_Y = 32;		//スコア表示開始位置　横（どこに表示するか）

static const char SCORE_PATH[] = "";

//タイトル画面の構造体
typedef struct {
	int m_graphHndl[NUMBER];	//画像ハンドル
	int m_soundHndl;			//効果音ハンドル
	int m_score;				//現在のスコア
	int m_dispScore;			//ディスプレイにお表示されているスコア
}SCORE_DATA;

SCORE_DATA g_number = { 0 };

//初期化
void CScore::InitScore(void)
{
	for (int i = 0; i < NUMBER; i++)
	{
		g_number.m_graphHndl[i] = -1;
	}
	g_number.m_soundHndl = -1;
	g_number.m_score = 0;
	g_number.m_dispScore = 0;
}

//ロード
void CScore::LoadScore(void)
{
	LoadDivGraph(SCORE_PATH, NUMBER, 10, 1,
		NUMBER_SIZE_X, NUMBER_SIZE_Y, g_number.m_graphHndl);
}

//データ破棄
void CScore::ExitScore(void)
{
	for (int i = 0; i < NUMBER; i++)
	{
		if (g_number.m_graphHndl[i] != -1)
		{
			DeleteGraph(g_number.m_graphHndl[i]);
			g_number.m_graphHndl[i] = -1;
		}
	}

}

//2d描画処理
void CScore::Draw2dScore(void)
{
	//モニターに表示するスコアを仮の変数にセット
	int TempScore = g_number.m_score;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//下１桁を取り出す
		int iNum = TempScore % 10;
		//1桁目を初期位置から表示

		DrawRotaGraph(START_POS_X - i * NUMBER_SIZE_X, START_POS_Y,
			1.0, 0.0, g_number.m_graphHndl[iNum], TRUE);
		//下一桁を削除
		TempScore /= 10;
	}
}


//3d描画処理
void CScore::Draw3dScore(VECTOR DrawPos, float Size)
{
	//モニターに表示するスコアを仮の変数にセット
	int TempScore = g_number.m_score;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//下１桁を取り出す
		int iNum = TempScore % 10;
		//1桁目をスコアを表示
		VECTOR Pos = DrawPos;
		Pos.x *= (float)i/3;

		//座標の微調整
		Pos.x += 45;

		//描画
		DrawBillboard3D(Pos,  0.5f, 0.5f, Size, 0.f, g_number.m_graphHndl[iNum], TRUE);

		//下一桁を削除
		TempScore /= 10;
	}
}


//スコアを加算する
void CScore::AddScore(int score)
{
	g_number.m_score += score;
}

//スコアを強制的にセットする
void CScore::SetScore(int score)
{
	g_number.m_score = score;
}

//取得する
int CScore::GetScore(void)
{
	return g_number.m_score;
}



