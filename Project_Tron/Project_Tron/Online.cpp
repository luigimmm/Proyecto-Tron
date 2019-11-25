#include "Online.h"
#include <iostream>
#include <SFML/Network.hpp>

using std::cout;
using std::string;

//Variables Globales
sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();

void Client::InitializeClient(string _jugador) {
	const unsigned short port = 5000;

	if (_jugador == "p1") {

		m_socketP1.connect(serverIp, port);
	}
	else if (_jugador == "p2") {

		m_socketP2.connect(serverIp, port);
	}
}

//---IMPORTANTE---
Server::Server(){}
Server::~Server(){}

//---IMPORTANTE---
Client::Client() {}
Client::~Client() {}