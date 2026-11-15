#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#define Max_main_menu 4
class MainMenu{
    // public means it can be accessed outside the class
public:
    MainMenu(float width, float height);
    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    void updateMousePosition(Vector2f mousePos);
    int getClickedItem(Vector2f mousePos);
    int MainMenuPressed() {
        return MainMenuSelected;
    }
    ~MainMenu();
    //private means it can be only used by the class internally and cannot be accessed outside of the said class.
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
};
//Draw MainMenu
//Move up
//Move down
