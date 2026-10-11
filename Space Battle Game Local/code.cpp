#include <SFML\Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
	sf::Window window; // Using the window class to define our window object
	window.create(sf::VideoMode({ 500, 500 }), "Space Battle", sf::Style::Default); // Creates the window and takes 3 parametres: 1.VideoMode which is a fucntion defines the size 2.Name of window 3. Style which is buttons
	
	window.setPosition({ 100, 100 }); // Change Position of the window on the screen
	
	window.setSize({ 700,700 }); // Chnage Size

	window.setTitle("Space Battle Game"); // Change Title

	sf::Vector2u size = window.getSize(); // Vector 2u is a type that stores 2 unsigned ints, getsize gets size of window
	int height = size.y;
	int width = size.x;

	bool focus = window.hasFocus(); // Checks whether the Window has focus

	while (window.isOpen()) // Keeps the Program running
	{
		while (const std::optional event = window.pollEvent()) // Optional is like a datatype that can either hold something(in case of some event like button pressed) or stay empty which will make it false and loop wont run. Pollevent checks for events
		{
			if (event->is<sf::Event::Closed>()) // If the event is pressing the close button
			{
				window.close(); // Close the Window
			}
		}
	}
}