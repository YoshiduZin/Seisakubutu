#pragma once
#include "../Base/Base.h"

class Game : public Base
{
public:
	Game();
	~Game();
	void Update();
	void Render();
	void Draw();
};
