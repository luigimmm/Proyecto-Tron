#include "Players.h"

//Funci�n para poder asignar un color para cada jugador
Player::Player(sf::Color _anyColor, const int _screenWidth, const int  _screenHeight) {
	
	mp_color = _anyColor;
	mp_x = _screenWidth / 2;
	mp_y = _screenHeight / 2;
	mp_dir = rand() % 4;
}

//
void Player::Mark(const int _screenWidth, const int  _screenHeight, sf::Time _deltaTime){

	sf::Vector2f movement(0, 0);

	//Posiciones a cambiar
	if (mp_dir == 2) { movement.x += 1; }
	if (mp_dir == 1) { movement.x -= 1; }
	if (mp_dir == 0) { movement.y += 1; }
	if (mp_dir == 3) { movement.y -= 1; }

	mp_circleS.move(movement * _deltaTime.asSeconds());

	//Limites
	if (mp_circleS.getPosition().x >= _screenWidth) { mp_circleS.setPosition(mp_circleS.getPosition().y, 0); }
	if (mp_circleS.getPosition().x < 0) { mp_circleS.setPosition(mp_circleS.getPosition().y, _screenWidth - 1); }
	if (mp_circleS.getPosition().y >= _screenHeight) { mp_circleS.setPosition(mp_circleS.getPosition().x, 0); }
	if (mp_circleS.getPosition().y < 0) { mp_circleS.setPosition(mp_circleS.getPosition().x, _screenHeight - 1); }
}


Player::Player(){}
Player::~Player(){}