#include "Players.h"

//Función para poder asignar un color para cada jugador
Player::Player(sf::Color _anyColor, const int _screenWidth, const int  _screenHeight){
	m_color = _anyColor;
	m_x = rand() % _screenWidth;
	m_y = rand() % _screenHeight;
	m_dir = rand() % 2;
}

//
void Player::Mark(const int _screenWidth, const int  _screenHeight){
	if (m_dir == 2) { m_x += 1; }
	if (m_dir == 1) { m_x -= 1; }
	if (m_dir == 0) { m_y += 1; }
	if (m_dir == 3) { m_y -= 1; }

	if (m_x >= _screenWidth) { m_x = 0; }
	if (m_x < 0) { m_x = _screenWidth - 1; }
	if (m_y >= _screenHeight) { m_y = 0; }
	if (m_y < 0) { m_y = _screenHeight - 1; }
}


Player::Player(){}
Player::~Player(){}