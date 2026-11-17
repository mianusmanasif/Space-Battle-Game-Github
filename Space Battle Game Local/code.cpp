#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include<string>
using namespace sf;
using namespace std;
int main();

void StartGame()
{
    const int width = 1920, height = 1080;
    sf::RenderWindow window; // Using the window class to define our window object
    window.create(sf::VideoMode({ width, height }), "Space Battle Game", sf::Style::Default); // Creates the window and takes 3 parametres: 1.VideoMode which is a fucntion defines the size 2.Name of window 3. Style which is buttons

    Texture texture;
    texture.loadFromFile("Texture/space1.JPG"); // we use texture from loaded file

    Sprite background(texture);
    background.setTexture(texture); // we set texture(image that we loaded) as background

    window.setFramerateLimit(30);
    //Creating Player
    Texture playerTexture;

    playerTexture.loadFromFile("Texture/Spaceship.png");

    Sprite player(playerTexture);
    player.setScale(Vector2f(0.15, 0.15));
    player.setPosition(Vector2f(width / 2, height / 1.4));

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

    // Score & Font Setup
    int score = 0;
    Font font;
    bool fontLoaded = font.openFromFile("Font/Orbitron.ttf");

    Text scoreText(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition({ 20.0f, 20.0f });
    scoreText.setString("Score: 0");

    // GAME OVER
    bool isGameOver = false;

    Text gameOverText(font);
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition({ width / 2.0f - 210.0f, height / 2.0f - 50.0f });

    while (window.isOpen()) // Keeps the Program running
    {
        while (const std::optional event = window.pollEvent()) //Look for events
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close(); // Close the Window
                main();
            }
        }
        // Time of each Frame
        Time timeSinceLastFrame = clock.restart();

        // FREEZE GAME WHEN GAME OVER
        if (!isGameOver)
        {
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
                bullet.setPosition({ player.getPosition().x + (player.getGlobalBounds().size.x / 2.0f) - (bullet.getGlobalBounds().size.x / 2.0f), player.getPosition().y });

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
            float fSpeed = 400.0f; //Use to adjust speed of Spaceship

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
                player.setPosition({ player.getPosition().x, 0 });
            }
            if (player.getPosition().x + boundingBox.size.x > width)
            {
                player.setPosition({ width - boundingBox.size.x, player.getPosition().y });
            }
            if (player.getPosition().y + boundingBox.size.y > height)
            {
                player.setPosition({ player.getPosition().x,height - boundingBox.size.y });
            }

            // Enemy Destroy N Score Count
            bool enemyDestroyed = false;

            for (size_t i = 0; i < bullets.size(); )
            {
                bool bulletHit = false;

                for (size_t j = 0; j < monsters.size(); )
                {
                    if (const optional intersection = bullets[i].getGlobalBounds().findIntersection(monsters[j].getGlobalBounds()))
                    {
                        monsters.erase(monsters.begin() + j);
                        bulletHit = true;
                        enemyDestroyed = true;
                        break;
                    }
                    else
                    {
                        j++;
                    }
                }

                if (bulletHit)
                {
                    bullets.erase(bullets.begin() + i);
                }
                else
                {
                    i++;
                }
            }

            if (enemyDestroyed == true)
            {
                score += 10;
                scoreText.setString("Score: " + to_string(score));
            }

            // Player-Enemy Touch Check
            for (size_t j = 0; j < monsters.size(); j++)
            {
                if (player.getGlobalBounds().findIntersection(monsters[j].getGlobalBounds()))
                {
                    isGameOver = true;
                    break;
                }
            }

        }
        // GAME OVER
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

        // Draw Score on Screen
        if (fontLoaded)
        {
            window.draw(scoreText);
        }

        // Draw Game Over Text
        if (fontLoaded && isGameOver)
        {
            window.draw(gameOverText);
        }

        window.display();
    }
}
