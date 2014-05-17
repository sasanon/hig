#include "Main.h"

#include <string>
#include <vector>
#include <fstream>

vector<string> split(const string &str, char delim){
	istringstream  iss(str);	string tmp; vector<string> res;
	while (getline(iss, tmp, delim)) res.push_back(tmp);
	return res;
}

// ステージの初期化
void CStage::Reset() {

	New<CBg>(CVector(-4, 0, 0));
	New<CBg>(CVector( 0, 0, 0));
	New<CBg>(CVector( 4, 0, 0));
	New<CBg>(CVector( 8, 0, 0));

	// ステージファイル読込
	std::string     str;	std::ifstream   ifs("MapData/stage01-02.txt");
	for (int y = 0; ifs; y++) {
		getline(ifs, str);                          // 1行読込
		vector<string> words = split(str, ',');     // ,で単語に分解
		for (int x = 0; x < words.size(); x++) {
			float a = x * 0.1f, b = -y*0.1f;
			if (!words[x].compare("K0"))	New<CBlock >(a, b, 0, 0, 0, TB_KEY_STAR * 100 + MB_STOP);     // ブロック(不動)
			if (!words[x].compare("Bl"))	New<CBlock >(a, b, 0, 0, 0, TB_CLOUD    * 100 + MB_STOP);     // ブロック(不動)
			if (!words[x].compare("Bx"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_XSIN);     // 左右に移動するブロック
			if (!words[x].compare("By"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_YSIN);     // 上下に移動するブロック
			if (!words[x].compare("Bc"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_CIRCLE);   // 円運動するブロック
			if (!words[x].compare("Bp"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_PENDULUM); // 振り子運動するブロック ★★★実装中！★★★
			if (!words[x].compare("MM"))	New<CMyShip>(a, b, 0, 0, 0, 0);                         // 主人公初期位置
			if (!words[x].compare("EE"))	New<CEnemy >(a, b, 0, 0, 0, 0);                         // 敵
			if (!words[x].compare("II"))	New<CItem  >(a, b, 0, 0, 0, 0);                         // アイテム(星)
		}
	}
}

// ステージの移動
void CStage::Move() {
	Time++;
}
