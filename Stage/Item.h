// ƒAƒCƒeƒ€
class CItem : public CMyMover {
public:
	void* operator new(size_t n) { return ItemList.New(n); }
	void operator delete(void* p) { ItemList.Delete(p); }
	CItem() : CMyMover(ItemList) {}
	void Reset();
	void Move();
};

