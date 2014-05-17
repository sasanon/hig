#ifndef Block_h
#define Block_h

// ブロック特性の定義
typedef enum{
	TB_NORMAL,		// 非破壊ブロック
	TB_CLOUD,		// 非破壊ブロック(雲)
	TB_BREAK,		// 破壊可能ブロック
	TB_KEY_STAR,	// 鍵ブロック(星)
	TB_KEY_CIRCLE,	// 鍵ブロック(円)
	TB_KEY_HEART,	// 鍵ブロック(ハート)
	TB_KEY_HEXAGRAM,	// 鍵ブロック(六芒星)
	TB_ITEM,		// アイテムブロック
	TB_MAX,
}TYPE_BLOCK;

// 移動特性の定義
typedef enum{
	MB_STOP,			// 動かない
	MB_X,				// 等速で横に行ったり来たり
	MB_XSIN,			// 加減速して横に行ったり来たり
	MB_Y,				// 等速で縦に行ったり来たり
	MB_YSIN,			// 加減速して縦に行ったり来たり
	MB_PENDULUM,		// 振り子運動
	MB_CIRCLE,			// 等速円運動
	MB_ABOVE_PLAYER,	// 追従して常にプレイヤーに
	MB_MAX,
}TYPE_MOVE;

// ブロック
class CBlock : public CMyMover {
public:
	void* operator new(size_t n) { return BlockList.New(n); }
	void operator delete(void* p) { BlockList.Delete(p); }
	CBlock() : CMyMover(BlockList) {}
	void Reset();
	void Move();
private:
	CVector MoveCenter;
};

#endif
