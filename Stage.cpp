#include "Main.h"

#include <string>
#include <vector>
#include <fstream>

vector<string> split(const string &str, char delim){
	istringstream  iss(str);	string tmp; vector<string> res;
	while (getline(iss, tmp, delim)) res.push_back(tmp);
	return res;
}

// �X�e�[�W�̏�����
void CStage::Reset() {

	New<CBg>(CVector(-4, 0, 0));
	New<CBg>(CVector( 0, 0, 0));
	New<CBg>(CVector( 4, 0, 0));
	New<CBg>(CVector( 8, 0, 0));

	// �X�e�[�W�t�@�C���Ǎ�
	std::string     str;	std::ifstream   ifs("MapData/stage01-02.txt");
	for (int y = 0; ifs; y++) {
		getline(ifs, str);                          // 1�s�Ǎ�
		vector<string> words = split(str, ',');     // ,�ŒP��ɕ���
		for (int x = 0; x < words.size(); x++) {
			float a = x * 0.1f, b = -y*0.1f;
			if (!words[x].compare("K0"))	New<CBlock >(a, b, 0, 0, 0, TB_KEY_STAR * 100 + MB_STOP);     // �u���b�N(�s��)
			if (!words[x].compare("Bl"))	New<CBlock >(a, b, 0, 0, 0, TB_CLOUD    * 100 + MB_STOP);     // �u���b�N(�s��)
			if (!words[x].compare("Bx"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_XSIN);     // ���E�Ɉړ�����u���b�N
			if (!words[x].compare("By"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_YSIN);     // �㉺�Ɉړ�����u���b�N
			if (!words[x].compare("Bc"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_CIRCLE);   // �~�^������u���b�N
			if (!words[x].compare("Bp"))	New<CBlock >(a, b, 0, 0, 0, TB_NORMAL   * 100 + MB_PENDULUM); // �U��q�^������u���b�N �������������I������
			if (!words[x].compare("MM"))	New<CMyShip>(a, b, 0, 0, 0, 0);                         // ��l�������ʒu
			if (!words[x].compare("EE"))	New<CEnemy >(a, b, 0, 0, 0, 0);                         // �G
			if (!words[x].compare("II"))	New<CItem  >(a, b, 0, 0, 0, 0);                         // �A�C�e��(��)
		}
	}
}

// �X�e�[�W�̈ړ�
void CStage::Move() {
	Time++;
}
