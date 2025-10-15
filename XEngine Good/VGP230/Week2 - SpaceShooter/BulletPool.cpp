#include "BulletPool.h"
#include "Bullet.h"

BulletPool::BulletPool()
	:Entity()
	, mNextAvailableIndex(0)
{

}

BulletPool::~BulletPool()
{
	XASSERT(mBullets.empty(), "BulletPool: Unload must be called");
}

void BulletPool::Load()
{
	const int maxBullets = 50;
	for (int i = 0; i < maxBullets; ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->Load();
		mBullets.push_back(bullet);
	}
}

void BulletPool::Update(float deltaTime)
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Update(deltaTime);
	}
}

void BulletPool::Render()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Render();
	}
}

void BulletPool::Unload()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Unload();
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
	mBullets.clear();
}

Bullet* BulletPool::GetBullet()
{
	Bullet* bullet = mBullets[mNextAvailableIndex];
	mNextAvailableIndex = (mNextAvailableIndex + 1) % mBullets.size();

	return bullet;
}

std::vector<Bullet*>& BulletPool::GetBullets()
{
	return mBullets;
}
