#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream> 
#include "script.h"

using namespace sf;
using namespace std;

int RETURN_CODE = 0;
sf::ContextSettings settings = sf::ContextSettings();


int main() {
	Font font;
	font.loadFromFile("font.ttf");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(50);
	text.setOutlineThickness(1.f);
	text.setOutlineColor(Color::Black);
	text.setPosition(Vector2f(5.f, 675.f));
	text.setString("");

	RectangleShape shapeT(Vector2f(50.f, 50.f));
	shapeT.setOutlineColor(Color::Black);
	shapeT.setOutlineThickness(1.f);

	settings.antialiasingLevel = 8;
	//                                                 25    14                                   //
	RenderWindow* window = new RenderWindow(VideoMode(1280, 750), "Turing", Style::Close, settings);
	vector<char> transistors;
	vector<string> script;
	unsigned short size = 0;
	unsigned short scriptlength = 0;
	bool running = false;
	bool declared = false;
	unsigned short loop = 0;
	int count = 0;
	string ilosc = "";
	string s = "";

	fstream stream;

	string BUFFOR = "";
	string DISPLAY = "";

	Clock clock;
	float dtime = 0.f;

	while (true) {
		Event e;
		while (window->pollEvent(e)) {
			if (e.type == e.Closed) {
				window->close();
			}

			else if (e.type == e.KeyPressed) {

				if (e.key.code == Keyboard::F4) {
					BUFFOR = "";
					DISPLAY = "";
					loop = 0;
					running = false;
					stream.open("length", std::ios::in);
					if (stream.good()) {
						getline(stream, ilosc);
						if (ilosc != "") {
							size = atoi(ilosc.c_str());
							if (size > 325) {
								size = 325;
							}
						}
						else {
							size = 1;
						}

						transistors.resize(size);
						for (int i = 0; i <= size; i++) {
							transistors[i] = 0;
						}
						declared = true;
					}
					stream.close();
				}

				else if (e.key.code == Keyboard::F5) {
					stream.open("script", std::ios::in);
					count = 0;
					if (stream.good()) {
						while (getline(stream, s)) {
							count++;
						}
					}
					stream.close();
					script.resize(count+1);
					stream.open("script", std::ios::in);
					if (stream.good()) {
						for (int i = 0; i < count; i++) {
							getline(stream, script[i]);
						}
					}
					stream.close();
				}

			}
			else if (e.key.code == Keyboard::F6) {
				running = true;
				clock.restart();
			}
		}
		if (!window->isOpen()) {
			break;
		}
		window->clear(Color::White);
		if (declared) {
			for (int i = 0; i < 13; i++) {
				int CNT = i * 25;
				if (CNT > size) {
					break;
				}
				for (int j = 0; j < 25; j++) {
					if (CNT + j > size) {
						break;
					}

					RectangleShape shape(shapeT);
					shape.setPosition(Vector2f(15.f + (j * 50), 10.f + (i * 50.f)));
					int n = CNT + j;
					if (transistors[n] == 1) {
						shape.setFillColor(Color::Green);
					}
					else {
						shape.setFillColor(Color::Red);
					}
					window->draw(shape);
				}
			}
		}
		window->draw(text);
		window->display();
		if (declared) {
			dtime += clock.restart().asSeconds();
			if (running) {
				if (dtime > 0.5f) {
					dtime = 0.f;
					command(script[loop], transistors, BUFFOR, DISPLAY);
					loop += 1;
					if (loop >= count) {
						loop = 0;
						running = false;
					}
				}
			}
		}
		text.setString(DISPLAY);
	}
	return RETURN_CODE;
}