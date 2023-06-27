#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include "FText.h"

#define DELETE_KEY '\b'
#define ENTER_KEY '\n'
#define CHARACTER_SIZE 30
#define LINE_SPACING 7
#define XOFFSET 100

enum {
  INS_CHAR,
  DELETE_CHAR,
  DELETE_LINE, 
  NEW_LINE
};

class TextBox {
  public:
    TextBox() {};
    TextBox(TextBox &from);
    TextBox(int charSize, std::wstring str, 
            sf::String (*encoding)(std::__1::wstring::iterator begin, 
                                   std::__1::wstring::iterator end),
                                   bool highlight);
    
    std::wstring getString();
    sf::FText getText();
    int getTextLen();

    void insert(int pos, std::wstring str);
    void erase(size_t beg, size_t end);
    
    void drawTo(sf::RenderWindow &window);
    int typeOn(sf::Event input, int chPos);
    void setPosition(int lnNumOnScr, int lineNum);

  private:
    sf::FText lnNum;
    sf::FText textBox;
    sf::String text;
    bool highlight;

    void colorText();
    int inputLogic(wchar_t charTyped, int chPos);
    int deleteChar(int chPos);
};

#endif // TEXTBOX_H
