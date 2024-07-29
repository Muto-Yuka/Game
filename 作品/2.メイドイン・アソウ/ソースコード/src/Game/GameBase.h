#pragma once

//ステージ基本クラス
//継承後も基本はpublicは増やさない
class CGameBase {
public:
	virtual ~CGameBase() {}		//デストラクタ
	virtual void Init() = 0;	//初期化
	virtual void Load() = 0;	//ロード
	virtual int Step() = 0;		//戻り値:次のシーン(-1なら変更なし)
	virtual void Draw() = 0;	//描画
	virtual void Exit() = 0;	//終了

	//リザルト情報を返す 0:待機　1:クリア　2:ゲームオーバー
	virtual int GetResult() = 0;	

};




