#include "Main.h"
#include <tchar.h>

// 変数
CMoverList StageList (sizeof(CStage ),   100);
CMoverList BgList    (sizeof(CBg    ),   100);
CMoverList MyShipList(sizeof(CMyShip),   100);
CMoverList EnemyList (sizeof(CEnemy ),  1000);
CMoverList WeaponList(sizeof(CWeapon), 10000);
CMoverList BulletList(sizeof(CBullet), 10000);
CMoverList EffectList(sizeof(CEffect), 10000);
CMoverList BlockList (sizeof(CBlock ), 10000);
CMoverList ItemList  (sizeof(CItem  ),  1000);
CMoverList CameraList(sizeof(CCamera),   100);
CMoverList LightList (sizeof(CLight ),   100);

CCamera *Camera, *CameraUI;
int Score;

// ゲーム本体
class CMyGame : public CGame {
public:
	int Time;
	bool Pause, PrevPause;
	CFont* Font;

	// 初期化
	CMyGame::CMyGame() : CGame(L"My Game") {
		const wchar_t fontchar[]=
			L"~|0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ,.(){}<>!?+-x*/='\\\"#$%&@[]";
		Font=new CFont(Graphics->GetDevice(), 
			ExePath+L"..\\Font\\Font.png", 0, fontchar, 
			16.0f/256, 32.0f/256, 16, 32, 2, 2);
		//NetworkInput.Open(Config.GetValue(L"Server"), Config.GetIntValue(L"Port"));
		Reset();
	}

	// リセット
	void Reset() {
		Sound->Stop();

		StageList.Clear();
		BgList.Clear();
		MyShipList.Clear();
		EnemyList.Clear();
		WeaponList.Clear();
		BulletList.Clear();
		EffectList.Clear();
		BlockList.Clear();
		ItemList.Clear();
		CameraList.Clear();
		LightList.Clear();

		Score=Time=0;
		Pause=PrevPause=false;

		Camera=New<CCamera>();
		CameraUI=New<CCamera>(0,0,0,0,0,1);
		New<CStage>();
	}

	// 移動
	void Move() {
		if (KeyState[0][DIK_C]) Reset();					// Cを押したらリセット
		if (!PrevPause && KeyState[0][DIK_V]) Pause=!Pause;	// Vを押したらポーズ
		PrevPause=KeyState[0][DIK_V];
		if (!Pause) {										// ポーズ中は全ての更新を停止
			StageList.Move();
			BgList.Move();
			MyShipList.Move();
			EnemyList.Move();
			WeaponList.Move();
			BulletList.Move();
			EffectList.Move();
			BlockList.Move();
			ItemList.Move();
			LightList.Move();
			CameraList.Move();

			Time++;
		}
	}

	// 描画
	void Draw() {
		CBasicRenderer& r=*Renderer;

		// 画面クリア
		r.Color=CColor(1, 1, 1, 1);	// クリア色設定？
		r.ClearRenderTarget=true;	// 描画前に画面をクリア指示ON
		r.Render();
		r.ClearRenderTarget=false;	// 描画前に画面をクリア指示OFF

		// マップ内オブジェクトの描画条件設定
		r.LightList=&LightList;
		r.Camera=Camera;
		r.Perspective=r.ZBuffer=r.Sort=r.Billboard=false;

		// 描画対象をマップ内オブジェクトへ変更
		r.Remove();			// 描画対象を一旦全削除
//		r.Add(StageList);
		r.Add(BgList);
		r.Add(ItemList);
		r.Add(BlockList);
		r.Add(EffectList);
		r.Add(WeaponList);
		r.Add(MyShipList);
		r.Add(EnemyList);
		r.Add(BulletList);
		// マップ内オブジェクトを全描画
		r.Render();

		// UIの描画条件設定
		r.LightList=&LightList;
		r.Camera=CameraUI;
		// 描画
		// 描画対象をUIオブジェクトへ変更
		r.Remove();			// 描画対象を一旦全削除
		// UIオブジェクトを全描画
		r.Render();

		// フォントの描画
		Font->DrawText(wstring(L"SCORE:")+ToStr(Score), 0, 0, CColor(1, 1, 1, 1), CColor(0, 0, 0, 1));
	}
};

// アプリケーションの起動
CMyGame* Game;
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, INT) {
	TCHAR szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szDir[_MAX_DIR];

	// 実行モジュールのフルパスを取得
	if(GetModuleFileName(NULL, szPath, sizeof(szPath)) == 0)	return S_FALSE;

	// パスからディレクトリを抽出してカレントディレクトリに設定
	_tsplitpath_s(szPath, szDrive,_MAX_DRIVE, szDir,_MAX_DIR, 0,0, 0,0); 
	_tcscpy_s(szPath,szDrive);
	_tcscat_s(szPath,szDir);
	if(!SetCurrentDirectory(szPath))	return S_FALSE;


	Game=new CMyGame();
	Game->Run();
	delete Game;
	return 0;
}

