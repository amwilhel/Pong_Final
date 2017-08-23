#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

Ball::Ball() {
}

//Create new ball with an initial velocity of 50, 50
Ball::Ball(RenderWindow &board){
	ball.setSize(Vector2f(10, 10));
	ball.setFillColor(sf::Color::White);
	ball.setPosition(400, 300);
	velocity = Vector2f(50, 50);
	board_size = Vector2f(board.getSize().x, board.getSize().y);
}

//Create new ball on the screen with a variable velocity
Ball::Ball(Vector2f vel, RenderWindow &board) {
	ball.setSize(Vector2f(10, 10));
	ball.setFillColor(sf::Color::White);
	ball.setPosition(400, 300);
	board_size = Vector2f(board.getSize().x, board.getSize().y);
	velocity = vel;
};

//Draw the ball
void Ball::Draw(RenderWindow &board) {
	board.draw(ball);
}

//Make the ball move within the screen boundaries
void Ball::Move(float time) {
	Vector2f pos = ball.getPosition() + velocity*time;
	ball.setPosition(pos);

	if (ball.getPosition().y >= board_size.y) {
		velocity.y = velocity.y * -1;
	}
	else if (ball.getPosition().y <= 0) {
		velocity.y = velocity.y * -1;
	}

}

//Set a new velocity for the ball
void Ball::setVelocity(Vector2f vel) {
	velocity = vel;
}

//Get the position of the ball
Vector2f Ball::getPosition() {
	return ball.getPosition();
}

//Set the position of the ball
void Ball::setPosition(Vector2f pos) {
	ball.setPosition(pos);
}