#include "Player.h"
#include <Novice.h>
void Player::Initalize()
{
	x_ = 500;
	y_ = 500;
	r_ = 16;
	speed_ = 5;
	isAlive_ = 1;
}

void Player::Update(char*keys)
{
	if (keys[DIK_A]) {
		x_ -= speed_;
	}
	if (keys[DIK_D]) {
		x_ += speed_;
	}
	if (keys[DIK_W]) {
		y_ -= speed_;
	}
	if (keys[DIK_S]) {
		y_ += speed_;
	}
}

void Player::Draw()
{
	if (isAlive_)
	{
		Novice::DrawEllipse(x_, y_, r_, r_, 0.0f, WHITE, kFillModeSolid);
	}
}

void Player::OnCollision()
{
	isAlive_ = 0;
}
