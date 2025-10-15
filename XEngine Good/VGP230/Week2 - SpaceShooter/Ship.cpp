#include "Ship.h"
#include "Bullet.h"

// Implementation
Ship::Ship()
	:Entity()
	, mImageId(0)
	, mPosition(0.0f)
	, mRotation(0.0f)
{

}

Ship::~Ship()
{

}

void Ship::Load()
{
	mImageId = X::LoadTexture("fighter.png");

	// Points out problem 
	XASSERT(mImageId != 0, "Ship: Failed to load image");

	// Center of the screen
	mPosition.x = X::GetScreenWidth() * 0.5f;
	mPosition.y = X::GetScreenHeight() * 0.5f;

	mBulletPool.Load();
}

void Ship::Update(float deltaTime)
{
	const float speed = 100.0f;
	const float turnSpeed = X::Math::kPiByTwo;

	// Forward and Backward
	if (X::IsKeyDown(X::Keys::W))
	{
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::S))
	{
		mPosition -= X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}

	// Left and Right
	if (X::IsKeyDown(X::Keys::A))
	{
		mRotation -= turnSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		mRotation += turnSpeed * deltaTime;
	}

	// Shoot bullet
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		X::Math::Vector2 bulletPos = mPosition + X::Math::Vector2::Forward(mRotation) * 50.0f;
		Bullet* bullet = mBulletPool.GetBullet();
		bullet->SetActive(bulletPos, mRotation, 3.0f);
	}

	mBulletPool.Update(deltaTime);
}

void Ship::Render()
{
	X::DrawSprite(mImageId, mPosition, mRotation);
	mBulletPool.Render();
}

void Ship::Unload()
{
	mBulletPool.Unload();
}