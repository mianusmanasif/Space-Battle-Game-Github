/*#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main()
{
	RenderWindow window( VideoMode( { 1920, 1080 } ), "SFML works!" );
	Texture playerTexture;
	playerTexture.loadFromFile("Texture/Spaceship.png");
	Sprite player(playerTexture);
	player.setScale(Vector2f(0.09,0.09));
	player.setPosition(Vector2f(860,780));

	Clock clock;

	while ( window.isOpen() )
	{
		Time timeSinceLastFrame=clock.restart();
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<Event::Closed>() )
				window.close();
		}
		Vector2f vRequestedPlayerMovement(0.0f,0.0f);
		float fSpeed=350.0f; //Use to adjust speed of Spaceship
		//Gather player's input

		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			vRequestedPlayerMovement+=Vector2f(0.0f,-1.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			vRequestedPlayerMovement+=Vector2f(1.0f,0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			vRequestedPlayerMovement+=Vector2f(0.0f,1.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			vRequestedPlayerMovement+=Vector2f(-1.0f,0.0f);
		}
		player.move(vRequestedPlayerMovement*timeSinceLastFrame.asSeconds()*fSpeed);


		window.clear();
		window.draw(player);
		window.display();
	}
}
*/