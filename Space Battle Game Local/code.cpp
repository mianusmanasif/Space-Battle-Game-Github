
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace sf;
using namespace std;

int main()
{
    const int width = 860, height = 800;
    sf::RenderWindow window; // Using the window class to define our window object
    window.create(sf::VideoMode({ width, height }), "Space Battle Game", sf::Style::Default); // Creates the window and takes 3 parametres: 1.VideoMode which is a fucntion defines the size 2.Name of window 3. Style which is buttons
   
    Texture texture;
    texture.loadFromFile("space1.JPG"); // we use texture from loaded file 

    Sprite background(texture);
    background.setTexture(texture); // we set texture(image that we loaded) as background

    window.setFramerateLimit(30);
    //Creating Player
    Texture playerTexture;

    playerTexture.loadFromFile("Texture/Spaceship.png");
   
    Sprite player(playerTexture);
    player.setScale(Vector2f(0.2, 0.2));
    player.setPosition(Vector2f(width/2, height/1.4));
    
    Clock clock;

    //Creating Monster
    Texture monsterTexture;
    monsterTexture.loadFromFile("Texture/Monster.png");

    Sprite monster(monsterTexture);
    monster.setScale(Vector2f(0.1, 0.1));

    vector<Sprite> monsters;
    monsters.push_back(Sprite(monster));

    int monsspawntimer = 0;

    // Creating bullet
    Texture bulletTexture;
    bulletTexture.loadFromFile("Texture/Bullet.png");

    Sprite bullet(bulletTexture);
    bullet.setScale(Vector2f(0.1, 0.05));

    vector<Sprite> bullets;

    bool mousePressed = false;

    while (window.isOpen()) // Keeps the Program running
    {
        while (const std::optional event = window.pollEvent()) //Look for events
        {
            if (event->is<sf::Event::Closed>()) 
            {
                window.close(); // Close the Window
            }
        }
        // Time of each Frame
        Time timeSinceLastFrame = clock.restart();

        //Monsters
        
        if (monsspawntimer < 30)
        {
            monsspawntimer++;
        }
        if (monsspawntimer >= 30)
        {
            monster.setPosition({ float(rand() % width - int(monster.getScale().x)), 0 });
            monsters.push_back(monster);

            monsspawntimer = 0;
        }
        for (int i = 0; i < monsters.size(); i++)
        {
            monsters[i].move(Vector2f(0, 200) * timeSinceLastFrame.asSeconds());

            if (monsters[i].getPosition().y > height)
            {
                monsters.erase(monsters.begin() + i);
            }
        }
        //Bullets;
        if (Mouse::isButtonPressed(Mouse::Button::Left) && !mousePressed)
        {
          
            bullet.setPosition({ player.getPosition().x + 32 , player.getPosition().y});

            bullets.push_back(bullet);

            mousePressed = true;
        }
        if (!Mouse::isButtonPressed(Mouse::Button::Left))
        {
            mousePressed = false;
        }
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(Vector2f(0, -500) * timeSinceLastFrame.asSeconds());

            if (bullets[i].getPosition().y < 0)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        //Spaceship

        Vector2f vRequestedPlayerMovement(0.0f, 0.0f);
        float fSpeed = 350.0f; //Use to adjust speed of Spaceship

        //Gather player's input 

        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
            vRequestedPlayerMovement += Vector2f(0.0f, -1.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            vRequestedPlayerMovement += Vector2f(1.0f, 0.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            vRequestedPlayerMovement += Vector2f(0.0f, 1.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            vRequestedPlayerMovement += Vector2f(-1.0f, 0.0f);
        }

        player.move(vRequestedPlayerMovement * timeSinceLastFrame.asSeconds() * fSpeed);

        //Adding boundaries to spaceship
        FloatRect boundingBox = player.getGlobalBounds();
        if (player.getPosition().x < 0)
        {
            player.setPosition({ 0, player.getPosition().y });
        }
        if (player.getPosition().y < 0)
        {
            player.setPosition({  player.getPosition().x, 0 });
        }
        if (player.getPosition().x + boundingBox.size.x > width)
        {
            player.setPosition({ width - boundingBox.size.x, player.getPosition().y });
        }
        if (player.getPosition().y + boundingBox.size.y > height)
        {
            player.setPosition({  player.getPosition().x,height - boundingBox.size.y });
        }

        //Collision between bullet and monster
        for (size_t i = 0; i < bullets.size();i++)
        {
            for (size_t j = 0; j < monsters.size();j++)
            {
                if (const optional intersection = bullets[i].getGlobalBounds().findIntersection(monsters[j].getGlobalBounds()))
                {
                    bullets.erase(bullets.begin() + i);
                    monsters.erase(monsters.begin() + j);

                    i--;
                    break;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(player);
        for (int i = 0; i < monsters.size(); i++)
        {
            window.draw(monsters[i]);
        }
        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }

        window.display();
    }
}
