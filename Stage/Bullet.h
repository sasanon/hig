// ’e
class CBullet : public CMyMover {
public:
	void* operator new(size_t n) { return BulletList.New(n); }
	void operator delete(void* p) { BulletList.Delete(p); }
	CBullet() : CMyMover(BulletList) {}
	void Reset();
	void Move();
private:
	CVector MoveVec;
};

