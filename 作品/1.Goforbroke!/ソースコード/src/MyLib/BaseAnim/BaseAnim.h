#pragma once
#include <DxLib.h>

//継承用基底モデルアニメーションクラス
class CBaseAnim
{
protected:
	enum ANIM_STATE				//アニメの状態
	{
		ANIMSTATE_NORMAL,		//通常再生
		ANIMSTATE_LOOP,			//ループ再生
		ANIMSTATE_END,			//一回のみ再生
		ANIMSTATE_NUM			//状態の数
	};

	typedef struct {
		int		m_iAnimHndl;	//アニメハンドル
		int		m_iID;			//再生中のアニメID
		int		m_iState;		//アニメの状態
		float	m_fEndFrm;		//アニメ全再生時間
		float	m_fFrm;			//アニメ再生時間
		float	m_fSpd;			//アニメ再生速度
		bool	m_bPlay;		//再生中かどうか　true:再生中
	}ANIM_DATA;

	ANIM_DATA m_sAnimData;		//構造体アニメ関連データ

	VECTOR m_vPos;				//モデル座標
	VECTOR m_vRot;				//回転角度
	VECTOR m_vScale;			//拡大縮小率
	VECTOR m_vSpeed;			//モデル速度
	int m_iHndl;				//モデルハンドル
	float m_fRadius;			//半径
	bool m_bSurvival;			//生存フラグ
	int m_HP;					//ｈｐ管理

public:
	virtual void Init();		//初期化
	virtual void Draw();		//描画処理
	virtual void Exit();		//終了処理
	virtual void UpData();		//更新処理

//ロード関数
	bool LoadModel(const char* pFilePath);		//モデル通常ロード
	bool DuplicateModel(int iModelHndl);		//モデル複製ロード
	void DeleteModel();							//モデル削除

//ゲッター・セッター
	inline VECTOR GetPosition() { return m_vPos; }	//座標取得
	bool IsSurvival() { return m_bSurvival; }		//生存フラグ

//アニメーション関連
	void UpdataAnim();
	//アニメＩＤ、再生速度、アニメのモデルハンドル、別モデルのアニメを使う場合アタッチするか
	void Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//ループアニメ　 アニメが最後まで再生されると最初に戻す
	void RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//エンドループ　　アニメが最後まで再生されても戻さずそのまま
	void RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

private:
	void DetachAnim();		//アニメをデタッチ
};



