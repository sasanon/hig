// ïêäÌ
class CWeapon : public CMyMover {
public:
	void* operator new(size_t n) { return WeaponList.New(n); }
	void operator delete(void* p) { WeaponList.Delete(p); }
	CWeapon() : CMyMover(WeaponList) {}
	void Reset();
	void Move();
};

