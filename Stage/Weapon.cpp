#include "../Main.h"

// ����̏�����
void CWeapon::Reset() {
	Texture=GetTexture(L"Weapon.png");
	Scale=CVector(1, 1, 1)*0.1f;	
}

// ����̈ړ�
void CWeapon::Move() {
}

