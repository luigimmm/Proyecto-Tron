#pragma once
#include <SFML/Network.hpp>
#include "Players.h"
#include <SFML/System.hpp>

class Server
{
	public:
	
		//Miembros
		sf::TcpListener ms_listener;
		sf::TcpSocket ms_socketP1;
		sf::TcpSocket ms_socketP2;
		sf::Packet ms_packetP1;
		sf::Packet ms_packetP2;
		
		Player *ms_objPlayerP1;
		Player *ms_objPlayerP2;

		bool field[800][900] = { 0 }; //Sirve para poder detectar la colisión
		bool ms_game = 1;
		
		unsigned int ms_whoWin = 0;
		//Metodos
		void
		InitializeServer(const int _screenWidth, const int  _screenHeight);

		void
		Run(const int _screenWidth, const int  _screenHeight);

		void
		Update(const int _screenWidth, const int  _screenHeight, sf::Time _deltaTime);


		Server() {};	//Constructor
		~Server() {};	//Destructor
};