#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include<string>
#include "MainMenu.h"
using namespace sf;
using namespace std;
int main();
void StartGame()
{
    const int width = 920, height = 1000;
    sf::RenderWindow window;
    window.create(sf::VideoMode({ width, height }), "Space Battle Game", sf::Style::Default);
    window.setPosition({ 500,0 });
    Texture texture;
    texture.loadFromFile("Texture/space1.JPG");

    Sprite background(texture);
    background.setTexture(texture);

    window.setFramerateLimit(30);
    //Creating Player
    Texture playerTexture;

    playerTexture.loadFromFile("Texture/Spaceship.png");

    Sprite player(playerTexture);
    player.setScale(Vector2f(0.12, 0.12));
    player.setPosition(Vector2f(width / 2, height / 1.4));

    Clock clock;

    //Creating Monsters (template sprites)
    Texture monsterTexture;
    monsterTexture.loadFromFile("Texture/Monster.png");



    Sprite monster(monsterTexture);
    monster.setScale(Vector2f(0.1, 0.1));

    Texture monster2texture;
    monster2texture.loadFromFile("Texture/Monster2.png");

    Sprite monster2(monster2texture);
    monster2.setScale(Vector2f(0.1, 0.1));

    // Creating bullet (template sprite)
    Texture bulletTexture;
    bulletTexture.loadFromFile("Texture/Bullet.png");

    Sprite bullet(bulletTexture);
    bullet.setScale(Vector2f(0.1, 0.05));

    // ---- Static arrays (store positions; template sprites are used to draw/collide) ----
    const int MAX_MONSTERS = 50;
    const int MAX_MONSTERS2 = 50;
    const int MAX_BULLETS = 100;

    Vector2f monsterPos[MAX_MONSTERS];
    int monsterCount = 0;

    Vector2f monster2Pos[MAX_MONSTERS2];
    int monster2HP[MAX_MONSTERS2];
    int monster2Count = 0;

    Vector2f bulletPos[MAX_BULLETS];
    int bulletCount = 0;
    int bullettimer = 0;

    // initial monsters (same as your original push_backs, at the sprites' starting position)
    monsterPos[monsterCount++] = monster.getPosition();
    monster2Pos[monster2Count] = monster2.getPosition();
    monster2HP[monster2Count] = 2;
    monster2Count++;

    // helpers (swap-remove: copy last element into slot j, shrink count)
    auto removeMonster = [&](int j) {
        monsterPos[j] = monsterPos[monsterCount - 1];
        monsterCount--;
    };
    auto removeMonster2 = [&](int j) {
        monster2Pos[j] = monster2Pos[monster2Count - 1];
        monster2HP[j] = monster2HP[monster2Count - 1];
        monster2Count--;
    };
    auto removeBullet = [&](int j) {
        bulletPos[j] = bulletPos[bulletCount - 1];
        bulletCount--;
    };
    // places a template sprite at a position and returns its bounds
    auto boundsAt = [](Sprite& s, Vector2f p) {
        s.setPosition(p);
        return s.getGlobalBounds();
    };

    int monsspawntimer = 0;
    int monsspawntimer2 = 0;

    bool mousePressed = false;
    bool spacePressed = false;

    // Explosion particles
    Texture particlesTexture;
    particlesTexture.loadFromFile("Texture/Particles.png");

    Sprite particles(particlesTexture);
    particles.setScale(Vector2f(0.05, 0.05));

    // Score & Font Setup
    int score = 0;
    Font font;
    bool fontLoaded = font.openFromFile("Font/Orbitron.ttf");

    //Options when game is over
    initializeGameOver(width, height);
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

    // Sounds
    SoundBuffer laserbuffer;
    laserbuffer.loadFromFile("Sounds/laser.mp3");
    Sound lasersound(laserbuffer);

    SoundBuffer hitbuffer;
    hitbuffer.loadFromFile("Sounds/hit.wav");
    Sound hitsound(hitbuffer);

    SoundBuffer gameoverbuffer;
    gameoverbuffer.loadFromFile("Sounds/gameover.wav");
    Sound gameoversound(gameoverbuffer);

    Music music;
    music.openFromFile("Sounds/Nach Punjaban - Abrar Ul Haq.mp3");

    music.play();
    music.setLooping(true);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                music.stop();
                main();
            }
            if (event->is<sf::Event::MouseMoved>())
            {
                if (isGameOver)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    updateGameOverMousePosition(Vector2f(mousePos));
                }
            }
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (isGameOver && event->getIf<sf::Event::MouseButtonPressed>()->button == Mouse::Button::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    int x = getClickedGameOverOption(Vector2f(mousePos));

                    if (x == 0)
                    {
                        window.close();
                        StartGame();
                        return;
                    }
                    else if (x == 1)
                    {
                        window.close();
                        music.stop();
                        main();
                        return;
                    }
                }
            }
        }
        // Time of each Frame
        Time timeSinceLastFrame = clock.restart();

        // FREEZE GAME WHEN GAME OVER
        if (!isGameOver)
        {
            //Monsters2
            if (monsspawntimer2 < 100)
            {
                monsspawntimer2++;
            }
            if (monsspawntimer2 >= 100)
            {
                if (monster2Count < MAX_MONSTERS2)
                {
                    monster2Pos[monster2Count] = { float(rand() % (width - 60) - int(monster2.getScale().x) + 30), 0.f };
                    monster2HP[monster2Count] = 2;
                    monster2Count++;
                }
                monsspawntimer2 = 0;
            }
            for (int i = 0; i < monster2Count; )
            {
                monster2Pos[i].y += 300 * timeSinceLastFrame.asSeconds();

                if (monster2Pos[i].y > height) removeMonster2(i);
                else i++;
            }

            //Monsters
            if (monsspawntimer < 30)
            {
                monsspawntimer++;
            }
            if (monsspawntimer >= 30)
            {
                if (monsterCount < MAX_MONSTERS)
                {
                    monsterPos[monsterCount] = { float(rand() % (width - 110) - int(monster.getScale().x) + 30), 0.f };
                    monsterCount++;
                }
                monsspawntimer = 0;
            }
            for (int i = 0; i < monsterCount; )
            {
                monsterPos[i].y += 200 * timeSinceLastFrame.asSeconds();

                if (monsterPos[i].y > height) removeMonster(i);
                else i++;
            }

            //Bullets
            bullettimer++;
            if ((Mouse::isButtonPressed(Mouse::Button::Left) && !mousePressed) || (Keyboard::isKeyPressed(Keyboard::Key::Space) && !spacePressed))
            {
                if (bulletCount < MAX_BULLETS && bullettimer > 15)
                {
                    bulletPos[bulletCount] = { player.getPosition().x + (player.getGlobalBounds().size.x / 2.0f) - (bullet.getGlobalBounds().size.x / 2.0f), player.getPosition().y };
                    bulletCount++;
                    bullettimer = 0;
                    lasersound.play();
                }
           
                mousePressed = true;
                spacePressed = true;

                
            }
            if (!Mouse::isButtonPressed(Mouse::Button::Left))
            {
                mousePressed = false;
            }
            if (!Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                spacePressed = false;
            }
            for (int i = 0; i < bulletCount; )
            {
                bulletPos[i].y -= 500 * timeSinceLastFrame.asSeconds();

                if (bulletPos[i].y < 0) removeBullet(i);
                else i++;
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
            if (player.getPosition().y + boundingBox.size.y > height - 80)
            {
                player.setPosition({ player.getPosition().x,height - 80 - boundingBox.size.y });
            }

            // Enemy Destroy N Score Count
            bool enemyDestroyed = false;
            bool enemy2Destroyed=false;

            for (int i = 0; i < bulletCount; )
            {
                bool bulletHit = false;

                for (int j = 0; j < monsterCount; j++)
                {
                    if (boundsAt(bullet, bulletPos[i]).findIntersection(boundsAt(monster, monsterPos[j])))
                    {
                        removeMonster(j);
                        bulletHit = true;
                        enemyDestroyed = true;
                        hitsound.play();
                        break;
                    }
                }

                if (bulletHit) removeBullet(i);
                else i++;
            }

            for (int i = 0; i < bulletCount; )
            {
                bool bulletHit = false;
                for (int j = 0; j < monster2Count; j++)
                {
                    if (boundsAt(bullet, bulletPos[i]).findIntersection(boundsAt(monster2, monster2Pos[j])))
                    {
                        bulletHit = true;
                        if (--monster2HP[j] <= 0)
                        {
                            removeMonster2(j);
                            enemy2Destroyed = true;
                            hitsound.play();
                        }
                        break;
                    }
                }

                if (bulletHit) removeBullet(i);
                else i++;
            }

            if (enemyDestroyed == true)
            {
                score += 10;
                scoreText.setString("Score: " + to_string(score));
            }
            if (enemy2Destroyed == true)
            {
                score += 15;
                scoreText.setString("Score: " + to_string(score));
            }


            // Player-Enemy Touch Check
            for (int j = 0; j < monsterCount; j++)
            {
                if (player.getGlobalBounds().findIntersection(boundsAt(monster, monsterPos[j])))
                {
                    isGameOver = true;
                    gameoversound.play();
                    break;
                }
            }
            for (int j = 0; j < monster2Count; j++)
            {
                if (player.getGlobalBounds().findIntersection(boundsAt(monster2, monster2Pos[j])))
                {
                    isGameOver = true;
                    gameoversound.play();
                    break;
                }
            }

        }
        // DRAW
        window.clear();
        window.draw(background);
        window.draw(player);
        for (int i = 0; i < monsterCount; i++)
        {
            monster.setPosition(monsterPos[i]);
            window.draw(monster);
        }
        for (int i = 0; i < monster2Count; i++)
        {
            monster2.setPosition(monster2Pos[i]);
            window.draw(monster2);
        }
        for (int i = 0; i < bulletCount; i++)
        {
            bullet.setPosition(bulletPos[i]);
            window.draw(bullet);
        }

        // Draw Score on Screen
        if (fontLoaded)
        {
            window.draw(scoreText);
        }

        // Draw Game Over Text and Options
        if (fontLoaded && isGameOver)
        {
            window.draw(gameOverText);
            music.pause();
            drawGameOverOptions(window);
        }
        window.display();
    }
}
