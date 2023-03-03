#ifndef DRAW_UI_HPP
#define DRAW_UI_HPP

#include <string>
#include "../colors.hpp"

void renderText(std::string text, int x, int y, color color,  bool centered);
void drawWindow(int x, int y, int width, int height, color fgColor, color bgColor);
void drawBorder(int x, int y, int width, int height, color fgColor, color bgColor);
void drawTileSelect(int x, int y);

#endif