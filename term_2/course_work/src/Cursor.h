#ifndef CURSOR_H
#define CURSOR_H
#include <SFML/Graphics.hpp>

class Cursor {
  public:
    int firstLine = 0;
    int linesOnScreen;
    int linesCount;
    int linePosOnScreen = 0;

    Cursor(int ln, int ch);
    Cursor();

    void setLinePos(int ln);
    void setCharPos(int ch);

    int getLinePos();
    int getCharPos();

    void moveDown(int lines = 1);
    void moveUp(int lines = 1);
    void moveLeft(int prevLineTextLen, int chs = 1);
    void moveRight(int curLineTextLen, int chs = 1);

    void drawTo(sf::RenderWindow &window, float xpos, float ypos);

  private:
    int chPos;   // char position from the beginning of line
    int linePos; // line position
};

#endif // CURSOR_H