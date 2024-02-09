#include "Enemy.h"
#include <Novice.h>
void Enemy::Initalize()
{
	x_ = 100;
	y_ = 100;
	r_ = 16;
	speed_ = 5;
	isAlive_ = 1;
}

void Enemy::Update()
{
	if (isAlive_ == 1)
	{
		x_ += speed_;
		if (x_ <= r_ || x_ >= 1280 - r_)
		{
			speed_ *= -1;
		}
	}
}

void Enemy::Draw()
{
	if (isAlive_ == 1)
	{
		Novice::DrawEllipse(x_,y_,r_,r_,0.0f,RED,kFillModeSolid);
	}
}

void Enemy::OnCollision()
{
	isAlive_ = 0;
}
