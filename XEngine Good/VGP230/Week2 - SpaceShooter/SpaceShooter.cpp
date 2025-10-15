#include <XEngine.h>
#include "Ship.h"


Ship mShip;


void GameInit()
{

	mShip.Load();
}

void GameRender()
{

}

bool GameLoop(float deltatime)
{
	mShip.Update(deltatime);
	mShip.Render();

	// Exit Application
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	mShip.Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}
