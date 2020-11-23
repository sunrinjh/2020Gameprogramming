#pragma once
#include <Zero.h>
#include "MapBase.h"
class MapManager : public ZeroIScene
{
	
public:
	MapManager();
	~MapManager();
	void SetMap(MapBase map);
	void Update(float eTime);
	void Render();
};

