#include "Main.h"
#include <tchar.h>

// �ϐ�
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

// �Q�[���{��
class CMyGame : public CGame {
public:
	int Time;
	bool Pause, PrevPause;
	CFont* Font;

	// ������
	CMyGame::CMyGame() : CGame(L"My Game") {
		const wchar_t fontchar[]=
			L"~|0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ,.(){}<>!?+-x*/='\\\"#$%&@[]";
		Font=new CFont(Graphics->GetDevice(), 
			ExePath+L"..\\Font\\Font.png", 0, fontchar, 
			16.0f/256, 32.0f/256, 16, 32, 2, 2);
		//NetworkInput.Open(Config.GetValue(L"Server"), Config.GetIntValue(L"Port"));
		Reset();
	}

	// ���Z�b�g
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

	// �ړ�
	void Move() {
		if (KeyState[0][DIK_C]) Reset();					// C���������烊�Z�b�g
		if (!PrevPause && KeyState[0][DIK_V]) Pause=!Pause;	// V����������|�[�Y
		PrevPause=KeyState[0][DIK_V];
		if (!Pause) {										// �|�[�Y���͑S�Ă̍X�V���~
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

	// �`��
	void Draw() {
		CBasicRenderer& r=*Renderer;

		// ��ʃN���A
		r.Color=CColor(1, 1, 1, 1);	// �N���A�F�ݒ�H
		r.ClearRenderTarget=true;	// �`��O�ɉ�ʂ��N���A�w��ON
		r.Render();
		r.ClearRenderTarget=false;	// �`��O�ɉ�ʂ��N���A�w��OFF

		// �}�b�v���I�u�W�F�N�g�̕`������ݒ�
		r.LightList=&LightList;
		r.Camera=Camera;
		r.Perspective=r.ZBuffer=r.Sort=r.Billboard=false;

		// �`��Ώۂ��}�b�v���I�u�W�F�N�g�֕ύX
		r.Remove();			// �`��Ώۂ���U�S�폜
//		r.Add(StageList);
		r.Add(BgList);
		r.Add(ItemList);
		r.Add(BlockList);
		r.Add(EffectList);
		r.Add(WeaponList);
		r.Add(MyShipList);
		r.Add(EnemyList);
		r.Add(BulletList);
		// �}�b�v���I�u�W�F�N�g��S�`��
		r.Render();

		// UI�̕`������ݒ�
		r.LightList=&LightList;
		r.Camera=CameraUI;
		// �`��
		// �`��Ώۂ�UI�I�u�W�F�N�g�֕ύX
		r.Remove();			// �`��Ώۂ���U�S�폜
		// UI�I�u�W�F�N�g��S�`��
		r.Render();

		// �t�H���g�̕`��
		Font->DrawText(wstring(L"SCORE:")+ToStr(Score), 0, 0, CColor(1, 1, 1, 1), CColor(0, 0, 0, 1));
	}
};

// �A�v���P�[�V�����̋N��
CMyGame* Game;
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, INT) {
	TCHAR szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szDir[_MAX_DIR];

	// ���s���W���[���̃t���p�X���擾
	if(GetModuleFileName(NULL, szPath, sizeof(szPath)) == 0)	return S_FALSE;

	// �p�X����f�B���N�g���𒊏o���ăJ�����g�f�B���N�g���ɐݒ�
	_tsplitpath_s(szPath, szDrive,_MAX_DRIVE, szDir,_MAX_DIR, 0,0, 0,0); 
	_tcscpy_s(szPath,szDrive);
	_tcscat_s(szPath,szDir);
	if(!SetCurrentDirectory(szPath))	return S_FALSE;


	Game=new CMyGame();
	Game->Run();
	delete Game;
	return 0;
}

