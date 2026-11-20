#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#define Max_main_menu 4

extern int MainMenuSelected;
extern Font font;
extern Text mainMenu[Max_main_menu];

void initializeMainMenu(float width, float height);
void draw(RenderWindow& window);
void MoveUp();
void MoveDown();
void updateMousePosition(Vector2f mousePos);
int getClickedItem(Vector2f mousePos);
int MainMenuPressed();

void initializeGameOver(float width, float height);
void drawGameOverOptions(RenderWindow& window);
void updateGameOverMousePosition(Vector2f mousePos);
int getClickedGameOverOption(Vector2f mousePos);
int GameOverOptionsPressed();