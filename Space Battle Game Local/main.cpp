#include <SFML/Graphics.hpp>
using namespace sf;
int main()
 {
    RenderWindow window(VideoMode(1200, 720), "Space Battle"); // window creaded with resolution of window also setted 

    Texture texture;
    texture.loadFromFile("space1.JPG"); // we use texture from loaded file 

    Sprite background;
    background.setTexture(texture); // we set texture(image that we loaded) as background

   
    while (window.isOpen())  // this is for continuesly open the window 
     {
        Event event;
        while (window.pollEvent(event)) // this is for having not intruption on any click on background
         {
            if (event.type == ::Event::Closed) // window will close only when we want to close other wise not
                window.close();
        }

        window.clear();
        window.draw(background); 
        window.display();
    }

    return 0;
}
