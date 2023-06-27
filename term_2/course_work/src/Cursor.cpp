#include "Cursor.h"

Cursor::Cursor(int ln, int ch) : linePos(ln), chPos(ch) {}

Cursor::Cursor() : Cursor(0, 0) {}

void Cursor::setLinePos(int ln) { linePos = ln; }
void Cursor::setCharPos(int ch) { chPos = ch; }

int Cursor::getLinePos() { return linePos; }
int Cursor::getCharPos() { return chPos; }

void Cursor::moveDown(int lns) {
    if (linePos + lns < linesCount) {
        linePos += lns;
        linePosOnScreen += lns;
        if (linePosOnScreen >= linesOnScreen) {
            linePosOnScreen = linesOnScreen;
            firstLine = linePos - linesOnScreen + 1;
        }
    }
}

void Cursor::moveUp(int lns) {
    if (linePos - lns >= 0) {
        linePos -= lns;
        linePosOnScreen -= lns;
        if (linePosOnScreen <= 0) {
            linePosOnScreen = 0;
            firstLine = linePos;
        }
    }
}

void Cursor::moveLeft(int prevLineTextLen, int chs) {
    if (chPos > 0)
        chPos -= chs;
    else {
        moveUp();
        chPos = prevLineTextLen;
    }
}

void Cursor::moveRight(int curLineTextLen, int chs) {
    if (chPos < curLineTextLen)
        chPos += chs;
    else if (linePos != linesCount - 1) {
        chPos = 0;
        moveDown();
    }
}

void Cursor::drawTo(sf::RenderWindow &window, float xpos, float ypos) {
    static sf::RectangleShape cursorRect(sf::Vector2f(3, 40));

    cursorRect.setFillColor(sf::Color::Red);
    cursorRect.setPosition(xpos, ypos);
    window.draw(cursorRect);
}