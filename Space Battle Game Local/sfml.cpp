#include <SFML/Graphics.hpp>
#include "MainMenu.h"
void StartGame();
using namespace sf;
int main() {
    //Make a main window
    RenderWindow MENU(VideoMode({920,1000}),"Main Menu",Style::Default);
    MENU.setPosition({ 500,0 });
    initializeMainMenu(MENU.getSize().x,MENU.getSize().y);

    while (MENU.isOpen()) {
        while (const optional event = MENU.pollEvent()) {
            int x = -1;
            if (event->is<Event::Closed>()) {
                MENU.close();
            }

            // KEYBOARD INPUT
            if (const auto* key = event->getIf<Event::KeyReleased>()) {
                if (key->code == Keyboard::Key::Up) {
                    MoveUp();
                }
                if (key->code == Keyboard::Key::Down) {
                    MoveDown();
                }
                if (key->code == Keyboard::Key::Enter) {
                    x = MainMenuPressed();
                }
            }

            // MOUSE HOVERING
            if (const auto* mouse = event->getIf<Event::MouseMoved>()) {
                Vector2f mousePos = MENU.mapPixelToCoords(mouse->position);
                updateMousePosition(mousePos);
            }

            // MOUSE CLICKING
            if (const auto* mouse = event->getIf<Event::MouseButtonPressed>()) {
                if (mouse->button == Mouse::Button::Left) {
                    Vector2f mousePos = MENU.mapPixelToCoords(mouse->position);
                    x = getClickedItem(mousePos);
                }
            }

            // MENU SELECTION
            if (x != -1) {
                RenderWindow ABOUT(VideoMode({920,1000}), "ABOUT");
                if (x == 0) {
                    MENU.close();
                    ABOUT.close();
                    StartGame();
                }
                if (x == 1) {

                    Font font;
                    font.openFromFile("Font/8514sys.ttf");

                    Text aboutText(font);
                    aboutText.setString("Made by Usman, Sami and Arif");
                    aboutText.setCharacterSize(50);
                    aboutText.setFillColor(Color::Red);
                    aboutText.setPosition({960, 540});
                    FloatRect bounds = aboutText.getGlobalBounds();

                    aboutText.move({
                        -bounds.size.x / 2.0f,
                        -bounds.size.y / 2.0f
                    });
                    while (ABOUT.isOpen()) {

                        while (const optional Aevent = ABOUT.pollEvent()) {
                            if (Aevent->is<Event::Closed>()) {
                                ABOUT.close();
                            }

                            if (const auto* Akey = Aevent->getIf<Event::KeyPressed>()) {
                                if (Akey->code == Keyboard::Key::Escape) {
                                    ABOUT.close();
                                }
                            }
                        }

                        ABOUT.clear();
                        ABOUT.draw(aboutText);
                        ABOUT.display();
                    }
                }
                if (x == 2) {
                    MENU.close();
                }
                break;
            }
        }
        MENU.clear();
        draw(MENU);
        MENU.display();
    }
}
