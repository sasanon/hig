// “G
class CEnemy : public CMyMover {
public:
	void* operator new(size_t n) { return EnemyList.New(n); }
	void operator delete(void* p) { EnemyList.Delete(p); }
	CEnemy() : CMyMover(EnemyList) {}
	void Reset();
	void Move();
private:
	CVector MoveVec;
};

