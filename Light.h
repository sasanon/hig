// ƒ‰ƒCƒg
class CLight : public CMyMover {
public:
	void* operator new(size_t n) { return LightList.New(n); }
	void operator delete(void* p) { LightList.Delete(p); }
	CLight() : CMyMover(LightList) {}
	void Reset();
	void Move();
};

