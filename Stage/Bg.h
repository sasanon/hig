// îwåi
class CBg : public CMyMover {
public:
	void* operator new(size_t n) { return BgList.New(n); }
	void operator delete(void* p) { BgList.Delete(p); }
	CBg() : CMyMover(BgList) {}
	void Reset();
	void Move();
};

