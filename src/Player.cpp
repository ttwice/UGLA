#include <GameObject.h>
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player() :
	GameObject(WIN_SIZE.x / 2, WIN_SIZE.y * 0.2, sf::RectangleShape { sf::Vector2f { 2 * U_P, 3 * U_P } })
{
	this->sprite.setFillColor(sf::Color(151, 77, 65));
	onGround = false;
	isDiving = false;
	facingRight = true;
}

void Player::moveRight(float dt)
{
	// apply accel
	velocity.x += HORIZONTAL_ACCEL * dt;

	// limit speed
	if (velocity.x > MAX_HORIZONTAL_SPEED)
		velocity.x = MAX_HORIZONTAL_SPEED;
}

void Player::moveLeft(float dt)
{
	// apply accel
	velocity.x -= HORIZONTAL_ACCEL * dt;

	// limit speed
	if (velocity.x < -MAX_HORIZONTAL_SPEED)
		velocity.x = -MAX_HORIZONTAL_SPEED;
}

void Player::jump()
{
	if (onGround)
	{
		velocity.y = JUMP_VEL;
	}
}

void Player::dive()
{
	// enable diving if in air
	isDiving = !onGround;
}

void Player::update(float dt)
{
	// 		HORIZONTAL MOVEMENT

	bool moving = false;
	if (sf::Keyboard::isKeyPressed(MOVE_RIGHT_KEY))
	{
		if (!isDiving)
		{
			moveRight(dt);
			moving = true;
		}
		facingRight = true;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_LEFT_KEY))
	{
		if (!isDiving)
		{
			moveLeft(dt);
			moving = true;
		}
		facingRight = false;
	}

	// move to slow down if not pressing move left or right keys
	if (!moving)
	{
		if (velocity.x > 0)
			velocity.x -= HORIZONTAL_ACCEL * dt;
		else if (velocity.x < 0)
			velocity.x += HORIZONTAL_ACCEL * dt;

		// stop player if vel is very small
		if (abs(velocity.x) < HORIZONTAL_ACCEL * dt / 2)
			velocity.x = 0;
	}

	//		VERTICAL MOVEMENT

	// apply gravity
	velocity.y -= (isDiving ? DIVE_COEFF : 1) * G * dt;
	if (velocity.y < -MAX_FALL_SPEED)
		velocity.y = -MAX_FALL_SPEED;

	position += velocity * dt;

	if (position.x > WIN_SIZE.x - size.x / 2)
	{
		position.x = WIN_SIZE.x - size.x / 2;
		velocity.x = 0;
	}
	else if (position.x < size.x / 2)
	{
		position.x = size.x / 2;
		velocity.x = 0;
	}

	if (position.y < size.y / 2)
	{
		position.y = size.y / 2;
		velocity.y = 0;
	}

	if (onGround)
	{
		isDiving = false;
	}
}