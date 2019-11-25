#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <time.h>
#include <string>
#include <cctype>
#include <iostream>
#include <string>


#include "Players.h"
#include "Online.h"

using std::cin;
using std::cout;
using std::string;

//Funciones
int GameLoop();

//Variables globales
sf::Packet packet1;
sf::Packet packet2;

bool game = 1;
bool winOrLose = true;
const int speedPlayer = 1;
const int screenWidth = 800;
const int screenHeight = 900;
const unsigned short port = 5000;
bool field[screenWidth][screenHeight] = { 0 }; //Sirve para poder detectar la colisión


//----------------------------------------------

int main() {

	char answer;
	string answerStd;
	Server objServer;
	Client objClient;

	cout << " Ingresa s, para ser el server o ingresa p1 o p2\n-->";z
	cin >> answerStd;

	if (answerStd == "s") {
		objServer.InitializeServer();
	}

	if (answerStd == "p1" || answerStd == "p2") {
		objClient.InitializeClient(answerStd);
	}
	return 0;
}

int GameLoop() {

	srand(time(0));	// Inicializa el generador de números aleatorios.

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "- > TRON < -");	//Para poder mostrar la ventana

	window.setFramerateLimit(60);	//Limite de fps

	//Declaración de variables
	sf::Texture texture;
	sf::Texture gameOver;
	sf::Sprite sprite;
	sf::RenderTexture rTexture;
	sf::Font fontWinner;
	
	
	texture.loadFromFile("background.jpg");	//Para cargar el fondo de imagen

	sf::Sprite spriteBackground(texture);

	rTexture.create(screenWidth, screenHeight);	//Necesario para poder dibujar el fondo del tamaño de la pantalla
	rTexture.setSmooth(true); //Función la textura aparece más suave para que los píxeles sean menos visibles.

	sprite.setTexture(rTexture.getTexture());

	rTexture.clear(); //Llamada de la función para borrar los contenidos anteriores del objetivo.
	rTexture.draw(spriteBackground);

	//Creación de jugadores
	Player p1(sf::Color(rand() % 255, rand() % 255, rand() % 255), screenWidth, screenHeight);
	Player p2(sf::Color(rand() % 255, rand() % 255, rand() % 255), screenWidth, screenHeight);

	//Texto
	fontWinner.loadFromFile("tron.ttf");	//Para cargar el tipo de fuente

	sf::Text textP1("JUGADOR 2, ES EL GANADOR", fontWinner, 45);
	sf::Text textP2("JUGADOR 1, ES EL GANADOR", fontWinner, 45);

	textP1.setPosition((screenWidth * 0.16) - 80, 520);	//Indicamos la posición en pantalla del texto
	textP2.setPosition((screenWidth * 0.16) - 80, 520);

	while (window.isOpen()){
		
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { if (p1.m_dir != 0) { p1.m_dir = 3; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { if (p1.m_dir != 3) { p1.m_dir = 0; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { if (p1.m_dir != 2) { p1.m_dir = 1; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { if (p1.m_dir != 1) { p1.m_dir = 2; } }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { if (p2.m_dir != 0) { p2.m_dir = 3; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { if (p2.m_dir != 3) { p2.m_dir = 0; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { if (p2.m_dir != 2) { p2.m_dir = 1; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { if (p2.m_dir != 1) { p2.m_dir = 2; } }


		//Condición para finalizar el juego
		if (!game) {
			window.clear();

			sf::Texture finalTexture;
			sf::Sprite finalSprite;

			finalTexture.loadFromFile("gameover.jpg");

			finalSprite.setTexture(finalTexture);


			if (winOrLose == true) {
				textP1.setFillColor(sf::Color::Green);
				window.draw(textP1);
			}
			if (winOrLose == false) {
				textP2.setFillColor(sf::Color::Green);
				window.draw(textP2);
			}
			
			window.draw(finalSprite);
			window.display();
			continue; 
		}


		for (int i = 0; i < speedPlayer; i++) {
			p1.Mark(screenWidth, screenHeight);
			p2.Mark(screenWidth, screenHeight);

			if (field[p1.m_x][p1.m_y] == 1) {
				game = 0; 
				winOrLose = true;
			}
			if (field[p2.m_x][p2.m_y] == 1) { 
				game = 0;
				winOrLose = false;
			}

			field[p1.m_x][p1.m_y] = 1;
			field[p2.m_x][p2.m_y] = 1;

			sf::CircleShape circle(3);
			circle.setPosition(p1.m_x, p1.m_y);
			circle.setFillColor(p1.m_color);    
			rTexture.draw(circle);

			circle.setPosition(p2.m_x, p2.m_y); 
			circle.setFillColor(p2.m_color);    
			rTexture.draw(circle);
			rTexture.display();
		}

		//Dibujamos
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}

void Server::InitializeServer() {

	m_listenerServer.listen(port);
	bool p1 = false;
	bool p2 = false;

	if (p1 != true) {

		m_listenerServer.accept(m_objClient.m_socketP1);
		cout << "\n\nDireccion IP del cliente 1 conectado - - > " << m_objClient.m_socketP1.getRemoteAddress() << std::endl;
		p1 = true;
	}
	if (p2 != true) {

		m_listenerServer.accept(m_objClient.m_socketP2);
		cout << "\n\nDireccion IP del cliente 2 conectado - - > " << m_objClient.m_socketP2.getRemoteAddress() << std::endl;
		p2 = true;
	}
	if (p1 == true && p2 == true) {

		sf::Thread juego1(GameLoop);
		sf::Thread juego2(GameLoop);

		juego1.launch();
		juego2.launch();
	}
}