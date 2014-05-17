#pragma once
#include "..\..\HigPen\HigPen.h"
using namespace higpen;

extern CMoverList 
	StageList, MyShipList, EnemyList, WeaponList, BulletList, BgList,
	EffectList, BlockList, ItemList, CameraList, LightList;

extern int Score;

#include "Stage/MyMover.h"
#include "Stage/Bg.h"
#include "Stage/Block.h"
#include "Stage/Bullet.h"
#include "Stage/Effect.h"
#include "Stage/Enemy.h"
#include "Stage/Item.h"
#include "Stage/MyShip.h"
#include "Stage/Weapon.h"
#include "Camera.h"
#include "Light.h"
#include "Stage.h"

extern CCamera* Camera;

