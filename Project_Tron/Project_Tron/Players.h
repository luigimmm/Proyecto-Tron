#pragma once
#include <SFML/Graphics.hpp>


class Player
{
	public:
		//---Miembros de SFML
		sf::Color m_color;

		//---Miembros
		int m_x;
		int m_y;
		int m_dir;

		//---Métodos
		void
		Mark(const int _screenWidth, const int  _screenHeight);

		//---Constructores
		Player();	
		Player(sf::Color _anyColor,const int _screenWidth, const int  _screenHeight);	//Constructor para poder indicar el color del jugador
		~Player();	//Destructor
};