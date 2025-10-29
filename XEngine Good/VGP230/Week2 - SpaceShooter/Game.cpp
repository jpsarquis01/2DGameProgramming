#include "Game.h"
#include "Ship.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ProgressBar.h"

Game::Game()
	:Entity()
	, mPlayer(nullptr)
	, mBulletPool(nullptr)
	, mHealthBar(nullptr)
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
	mHealthBar = new ProgressBar();

	mHealthBar->Load();

	mPlayer->Load();
	mPlayer->SetBulletPool(mBulletPool);
	AddCollidable(mPlayer);

	X::Math::Vector2 spawnPos = X::Math::Vector2::Zero();
	X::Math::Vector2 spawnDirection = X::Math::Vector2::Zero();
	X::Math::Vector2 center = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	const float minOffset = 100.0f;
	const float maxOffset = center.y;
	for (int i = 0; i < 10; ++i)
	{
		spawnDirection = X::RandomUnitCircle();
		spawnPos = center + spawnDirection * X::RandomFloat(minOffset, maxOffset);

		Enemy* newEnemy = new Enemy();
		newEnemy->Load();
		newEnemy->SetBulletPool(mBulletPool);
		newEnemy->SetShip(mPlayer);
		newEnemy->SetPosition(spawnPos);
		newEnemy->SetRotation(X::RandomFloat() * X::Math::kTwoPi);
		AddCollidable(newEnemy);
		mEnemies.push_back(newEnemy);
	}

	mBulletPool->Load();
	std::vector<Bullet*>& bullets = mBulletPool->GetBullets();
	for (Bullet* bullet : bullets)
	{
		AddCollidable(bullet);
	}
}

void Game::Update(float deltaTime)
{
	mPlayer->Update(deltaTime);
	mBulletPool->Update(deltaTime);

	for (Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}

	int numCollidable = mCollidables.size();
	for (int i = 0; i < numCollidable - 1; ++i)
	{
		for (int n = i + 1; n < numCollidable; ++n)
		{
			if (mCollidables[i]->DiCollide(mCollidables[n]))
			{
				mCollidables[i]->OnCollition(mCollidables[n]);
				mCollidables[n]->OnCollition(mCollidables[i]);
			}
		}
	}

	mHealthBar->SetBarValue(mPlayer->GetHealth(), mPlayer->GetMaxHealth());
}

void Game::Render()
{
	mPlayer->Render();
	for (Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}
	mBulletPool->Render();
	mHealthBar->Render();
}

void Game::Unload()
{
	mBulletPool->Unload();
	delete mBulletPool;
	mBulletPool = nullptr;


	mHealthBar->Unload();
	delete mHealthBar;
	mHealthBar = nullptr;

	mPlayer->Unload();
	delete mPlayer;
	mPlayer = nullptr;

	for (Enemy* enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
		enemy = nullptr;
	}
	mEnemies.clear();
}

void Game::AddCollidable(Collidable* collidable)
{
	mCollidables.push_back(collidable);
}

bool Game::IsGameOver()
{
	return !mPlayer->IsAlive();
}

