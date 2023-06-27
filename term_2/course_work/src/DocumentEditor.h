#ifndef DOCUMENT_EDITOR_H
#define DOCUMENT_EDITOR_H
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <locale>
#include "Cursor.h"
#include "FText.h"
#include "TextBox.h"

class DocumentEditor {
  public:
    DocumentEditor(sf::String (*encoding)(std::__1::wstring::iterator begin,
                                          std::__1::wstring::iterator end),
                   bool highlight);
    void open(std::string path);
    void save();
    void view(sf::RenderWindow &wnd);
    void scrollUp(int lines = 1);
    void scrollDown(int lines = 1);
    void moveLeft(int chs = 1);
    void moveRight(int chs = 1);
    void typeOn(sf::Event event);
    ~DocumentEditor();

  private:
    std::string path;
    sf::String (*encoding)(std::__1::wstring::iterator begin, 
                           std::__1::wstring::iterator end);
    std::vector<TextBox *> content;
    bool edited;
    bool highlight;
    Cursor cursor;
};

#endif // DOCUMENT_EDITOR_H