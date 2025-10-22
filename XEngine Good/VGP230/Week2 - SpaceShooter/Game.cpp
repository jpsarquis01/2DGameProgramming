#include "Game.h"
#include "Ship.h"
#include "BulletPool.h"
#include "Bullet.h"

Game::Game()
	:Entity()
	, mPlayer(nullptr)
	, mBulletPool(nullptr)
{

}

Game::~Game()
{
	XASSERT(mPlayer == nullptr, "Game: Unload must be called");
}

void Game::Load()
{
	mPlayer = new Ship();
	mBulletPool = new BulletPool();
}

void Game::Update(float deltaTime)
{

}

void Game::Render()
{
	mPlayer->Render();
	mBulletPool->Render();
}

void Game::Unload()
{
	mBulletPool->Unload();
	delete mBulletPool;
	mBulletPool = nullptr;

	mPlayer->Unload();
	delete mPlayer;
	mPlayer = nullptr;
}

void Game::AddCollidable(Collidable* collidable)
{
	mCollidables.push_back(collidable);
}

bool Game::IsGameOver()
{
	return false;
}

