#include "Number.h"

//定義関連---------------------------------------------------------------------------
#define  NUMBER (10)				//読み込む画像数「０」～「９」
#define NUMBER_SIZE_X (48)			//数字サイズ横(画像サイズ)
#define NUMBER_SIZE_Y (32)			//数字サイズ縦(画像サイズ)
#define DIGIT_NUMBER (1)			//表示可能な桁数
#define ADD_SCORE_SPD (10)			//１フレームで加算されるスコア数

#define START_POS_X (580)			//スコア表示開始位置　横（どこに表示するか）
#define START_POS_Y (32)			//スコア表示開始位置　横（どこに表示するか）

//タイトル画面の構造体
typedef struct {
	int m_graphHndl[NUMBER];		//画像ハンドル
	int m_score;					//現在のスコア
	int m_dispScore;				//ディスプレイにお表示されているスコア
}NUMBER_DATA;

//---------------------------------------------------------------------------------------

//この変数に実際のスコアなどのデータを格納する
NUMBER_DATA g_number = { 0 };

//----------------------------------------
//			初期化
//----------------------------------------
void CNumber::InitNumber(void)
{
	for (int i = 0; i < NUMBER; i++)
	{
		g_number.m_graphHndl[i] = -1;
	}
	g_number.m_score = 0;
	g_number.m_dispScore = 0;
}

//----------------------------------------
//			ロード
//----------------------------------------
void CNumber::LoadNumber(void)
{
	LoadDivGraph("data/Game/Item/Water/Number/Number.png", NUMBER, 6, 2,
		NUMBER_SIZE_X, NUMBER_SIZE_Y, g_number.m_graphHndl);
}

//-----------------------------------------
//			データ破棄
//-----------------------------------------
void CNumber::ExitNumber(void)
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

//-----------------------------------------
//			2d描画処理
//-----------------------------------------
void CNumber::Draw2dNumber(void)
{
	//モニターに表示するスコアを仮の変数にセット
	int TempScore = g_number.m_score;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//下１桁を取り出す
		int iNum = TempScore % 10;
		//1桁目を初期位置X=580、Y=32からスコアを表示していく

		DrawRotaGraph(START_POS_X - i * NUMBER_SIZE_X, START_POS_Y,
			1.0, 0.0, g_number.m_graphHndl[iNum], TRUE);
		//下一桁を削除
		TempScore /= 10;
	}
}


//-----------------------------------------
//			3d描画処理
//-----------------------------------------
void CNumber::Draw3dNumber(VECTOR DrawPos, float Size)
{
	//モニターに表示するスコアを仮の変数にセット
	int TempScore = g_number.m_score;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//下１桁を取り出す
		int iNum = TempScore % 10;
		//1桁目をスコアを表示していく
		VECTOR Pos = DrawPos;
		Pos.x *= (float)i / 3;

		//座標の微調整
		Pos.x += 50;

		//３ｄ空間に貼り付け 座標/中心座標/画像サイズ/回転角度/ハンドル/透明度を有効にするか/
		DrawBillboard3D(Pos, 0.5f, 0.5f, Size, 0.f, g_number.m_graphHndl[iNum], TRUE);

		//下一桁を削除
		TempScore /= 10;
	}
}


//----------------------------------------
//			加算する
//----------------------------------------
void CNumber::AddNumber(int score)
{
	//繰り上げない
	if (g_number.m_score < NUMBER - 1)
		g_number.m_score += score;
}

//----------------------------------------
//			強制的にセットする
//------------------------------------------
void CNumber::SetNumber(int score)
{
	g_number.m_score = score;
}

//-----------------------------------------
//			取得する
//-----------------------------------------
int CNumber::GetNumber(void)
{
	return g_number.m_score;
}

//-----------------------------------------
//			情報更新
//------------------------------------------
void CNumber::UpdateNumber()
{

}