// ���[�V������`
typedef enum{
	M_WAIT_R,		// �ҋ@(�E)
	M_WALK_R,		// ���s(�E)
	M_JUMPUP_R,		// �W�����v�㏸(�E)
	M_JUMPDOWN_R,	// �W�����v���~(�E)
	M_WAIT_L,		// �ҋ@(��)
	M_WALK_L,		// ���s(��)
	M_JUMPUP_L,		// �W�����v�㏸(��)
	M_JUMPDOWN_L,	// �W�����v���~(��)
	M_MAX,			// �����[�V������
}MOTION_ID;

// ���@
class CMyShip : public CMyMover {
public:
	void* operator new(size_t n) { return MyShipList.New(n); }
	void operator delete(void* p) { MyShipList.Delete(p); }
	CMyShip() : CMyMover(MyShipList) {}
	void Reset();
	void Move();
private:
	BYTE frameid;
	MOTION_ID motid;
	BYTE framemax[10];
};

