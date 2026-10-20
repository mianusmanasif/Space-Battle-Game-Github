#include <SFML/Graphics.hpp>

int main()
 {
    sf::RenderWindow window(sf::VideoMode(1200, 720), "Space Battle");

    sf::Texture texture;
    texture.loadFromFile("space1.JPG"); 

    sf::Sprite background;
    background.setTexture(texture);

   
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background); 
        window.display();
    }

    return 0;
}