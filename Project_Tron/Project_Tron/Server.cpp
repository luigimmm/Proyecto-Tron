#include "Server.h"
#include <iostream>


//Función para inicializar el server y los clientes
void Server::InitializeServer(const int _screenWidth, const int  _screenHeight){

	ms_listener.listen(5000); //Escuchamos quien entrará por ese puerto

	if (ms_listener.accept(ms_socketP1) == sf::Socket::Done) {//Aceptamos la entrada del juegador 1

		ms_objPlayerP1 = new Player(sf::Color(rand() % 255, rand() % 255, rand() % 255), _screenWidth, _screenHeight);	//Generamos el primer jugador
		ms_packetP1 << ms_objPlayerP1->mp_x << ms_objPlayerP1->mp_y << ms_objPlayerP1->mp_dir << ms_objPlayerP1->mp_color.toInteger();	//Desde el servidor guardamos la ubicación del P1 en un paquete

		if (ms_socketP1.send(ms_packetP1) == sf::Socket::Done) {

			std::cout << "\nINITIALIZE SERVER, Paquete enviado del jugador 1\n";
		}
		else {

			std::cout << "\nINITIALIZE SERVER, Error al enviar el paquete del jugador 1\n";
		}

		ms_socketP1.setBlocking(false);
	}

	ms_listener.listen(5000); //Escuchamos quien entrará por ese puerto por segunda vez

	if (ms_listener.accept(ms_socketP2) == sf::Socket::Done) {	//Aceptamos la entrada del juegador 2

		ms_objPlayerP2 = new Player(sf::Color(rand() % 255, rand() % 255, rand() % 255), _screenWidth, _screenHeight); //Generamos el primer jugador
		ms_packetP2 << ms_objPlayerP2->mp_x << ms_objPlayerP2->mp_y << ms_objPlayerP2->mp_dir << ms_objPlayerP2->mp_color.toInteger();	//Desde el servidor guardamos la ubicación del P1 en un paquete

		if (ms_socketP2.send(ms_packetP2) == sf::Socket::Done) {

			std::cout << "\nINITIALIZE SERVER, Paquete enviado del jugador 2\n";
		}
		else {

			std::cout << "\nINITIALIZE SERVER, Error al enviar el paquete del jugador 2\n";
		}

		ms_socketP2.setBlocking(false);
	}
}

//Función para indicar procesos escenciales del juego
void Server::Run(const int _screenWidth, const int  _screenHeight){
	
	//Variables
	sf::Clock clock;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time time = sf::Time::Zero;

	while (ms_game) {

		time += clock.restart();
		while (time > timePerFrame) {

			time -= timePerFrame;

			//Equivalencia al proceso de eventos
			if (ms_socketP1.receive(ms_packetP1) == sf::Socket::Done) {

				std::cout << "\nRUN SERVER, Se recibio la informacion del jugador 1\n";
				ms_packetP1 >> ms_objPlayerP1->mp_dir;	//Proceso la dirección del objeto
			}
			else {

				std::cout << "\nRUN, Error del server, no se recibio la info del jugador 1\n";
			}
			if (ms_socketP2.receive(ms_packetP1) == sf::Socket::Done) {

				std::cout << "\nRUN SERVER, Se recibio la informacion del jugador 2\n";
				ms_packetP2 >> ms_objPlayerP2->mp_dir;	//Proceso la dirección del objeto
			}
			else {

				std::cout << "\nRUN, Error del server, no se reciio la info del jugador 2\n";
			}

			Update(_screenWidth, _screenHeight, timePerFrame); //Mandamos a actualizar la nueva información
			
			//Condición de victoria
			if (ms_whoWin == 1 || ms_whoWin == 2) {

				ms_packetP1 << ms_whoWin;
				ms_packetP2 << ms_whoWin;
			}
			//Juego normal
			else {

				ms_packetP1 << ms_objPlayerP2->mp_dir;

				if (ms_socketP1.send(ms_packetP1) != sf::Socket::Done) {

					std::cout << "\nError, no se puedo enviar la info del socket 1\n";
				}

				ms_packetP2 << ms_objPlayerP1->mp_dir;
				if (ms_socketP2.send(ms_packetP2) != sf::Socket::Done) {

					std::cout << "\nError, no se puedo enviar la info del socket 2\n";
				}
			}
		}
	}
}

//Función para poder actualizar en pantalla los cambios
void Server::Update(const int _screenWidth, const int  _screenHeight, sf::Time _deltaTime){

	ms_objPlayerP1->Mark(_screenWidth, _screenHeight, _deltaTime);
	ms_objPlayerP2->Mark(_screenWidth, _screenHeight, _deltaTime);
	
	//Detección de colisiones
	if (field[ms_objPlayerP1->mp_x][ms_objPlayerP1->mp_y] == 1) {

		ms_game = 0;
		ms_whoWin = 1;
	}
	if (field[ms_objPlayerP1->mp_x][ms_objPlayerP1->mp_y] == 1) {
		
		ms_game = 0;
		ms_whoWin = 2;
	}
}
