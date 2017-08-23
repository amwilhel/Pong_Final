#include "Ball.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;
using namespace std;

void update_state(float dt);
void render_frame();

RenderWindow window;
RectangleShape shape;
Texture tex;
SoundBuffer buf;
Sound sound;
Ball ball;
Paddle paddle1;
Paddle paddle2;
int score1;
int score2;
Font font;
Text gameover;
bool isgameover;


int main()
{
	//Set up the game
	isgameover = false;

	window.create(VideoMode(800, 600), "Pong");
	ball = Ball (Vector2f(100, -100), window);
	paddle1.setPosition(Vector2f(760,200));
	paddle2.setPosition(Vector2f(20,200));
	score1 = 0;
	score2 = 0;

	//Set up fonts, sounds, and textures
	font.loadFromFile("ITCBLKAD.TTF");
	buf.loadFromFile("pistol.wav");
	sound.setBuffer(buf);
	sound.play();
	tex.loadFromFile("cowboy.png");
	shape.setSize(Vector2f(400, 250));
	shape.setPosition(200, 100);
	shape.setTexture(&tex);

	//Set up updates and timing
	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();

		update_state(dt);
		render_frame();
		window.display();
	}

	return 0;
}

void update_state(float dt)
{   
	//Play a new game when you press space bar
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (isgameover) {
			score1 = 0;
			score2 = 0;
			ball.setVelocity(Vector2f(100, 100));
			ball.setPosition(Vector2f(400, 300));
			gameover.setString("");
			isgameover = false;
			sound.play();
		}
		
	}
	

	//Play the game : Move the ball and paddles
	ball.Move(dt);


	//Control the player paddle
	Vector2f pos = paddle1.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (pos.y >= 0)
		pos.y -= 200 * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (pos.y <= window.getSize().y-80)
			pos.y += 200 * dt;
	}
	paddle1.setPosition(pos);


	//Control the .ai paddle
	pos = paddle2.getPosition();
	
	if (pos.y >= ball.getPosition().y-40) {
		if (pos.y >= 0)
			pos.y -= 200 * dt;
	}
	if (pos.y <= ball.getPosition().y-40) {
		if (pos.y <= window.getSize().y - 80)
			pos.y += 200 * dt;
	}
	paddle2.setPosition(pos);


	//Check if ball hits paddle1 or paddle2 and return the ball
	if (ball.getPosition().y <= paddle1.getPosition().y+80 && ball.getPosition().y >= paddle1.getPosition().y && ball.getPosition().x <= paddle1.getPosition().x+20 && ball.getPosition().x >= paddle1.getPosition().x) {
		float ballpos = ball.getPosition().y-paddle1.getPosition().y;
		ball.velocity.x = ball.velocity.x * -1;
		ball.velocity.y += ballpos;
		sound.play();
		ball.setVelocity(Vector2f (ball.velocity.x*1.1, ball.velocity.y*1.1));
	}

	if (ball.getPosition().y <= paddle2.getPosition().y + 80 && ball.getPosition().y >= paddle2.getPosition().y && ball.getPosition().x <= paddle2.getPosition().x + 20 && ball.getPosition().x >= paddle2.getPosition().x) {
		float ballpos = ball.getPosition().y-paddle2.getPosition().y;
		ball.velocity.x = ball.velocity.x * -1;
		ball.velocity.y += ballpos;
		sound.play();
		ball.setVelocity(Vector2f (ball.velocity.x*1.1, ball.velocity.y*1.1));
	}


	//If the ball is not hit by a paddle check that ball went out of bounds and update score
	if (ball.getPosition().x >= window.getSize().x) {
		score1++;
		ball.setPosition(Vector2f(400, 300));
		ball.setVelocity(Vector2f(100, 100));
		if (score1 < 5)
			sound.play();
	}
	if (ball.getPosition().x <= 0) {
		score2++;
		ball.setPosition(Vector2f(400, 300));
		ball.setVelocity(Vector2f(100, 100));
		if (score2 < 5) 
			sound.play();
		
	}

	//Check if gameover
	if (score1 == 5) {
		gameover.setString("Game Over. Player 1 Wins!");
		ball.setVelocity(Vector2f(0,0));
		ball.setPosition(Vector2f(400, 300));
		isgameover = true;
	}
	else if (score2 == 5) {
		gameover.setString("Game Over. Player 2 Wins!");
		ball.setVelocity(Vector2f(0, 0));
		ball.setPosition(Vector2f(400, 300));
		isgameover = true;
	}
}

//Draw all the UI elements
void render_frame()
{

	Text text1;
	Text text2;
	Text text3;

	window.clear(Color(0, 0, 0));
	window.draw(shape);
	paddle1.Draw(window);
	paddle2.Draw(window);
	ball.Draw(window);
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	gameover.setFont(font);
	text1.setCharacterSize(200);
	text2.setCharacterSize(200);
	text3.setCharacterSize(100);
	gameover.setCharacterSize(75);
	text1.setString(to_string(score1));
	text2.setString(to_string(score2));
	text3.setString("Pistol Pong");
	text1.setFillColor(Color::White);
	text2.setFillColor(Color::White);
	text3.setFillColor(Color::White);
	gameover.setFillColor(Color::Yellow);
	text1.setPosition(150, 20);
	text2.setPosition(550, 20);
	text3.setPosition(200, 5);
	gameover.setPosition(40, 400);
	window.draw(text1);
	window.draw(text2);
	window.draw(text3);
	window.draw(gameover);
}