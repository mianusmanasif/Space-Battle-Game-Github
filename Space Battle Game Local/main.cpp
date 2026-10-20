#include <SFML/Graphics.hpp>
using namespace sf;
int main()
 {
    RenderWindow window(sf::VideoMode(1200, 720), "Space Battle");

    Texture texture;
    texture.loadFromFile("space1.JPG"); 

    Sprite background;
    background.setTexture(texture);

   
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == ::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background); 
        window.display();
    }

    return 0;
}
