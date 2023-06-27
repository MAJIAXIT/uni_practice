#include "DocumentEditor.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace std;

#define HEIGHT 1800
#define WIDTH 1400

char *getCmdFlag(char **begin, char **end, const std::string &flag);
bool cmdFlagExists(char **begin, char **end, const std::string &flag);

/*  Flags:
 *  -no_highlight
 *  -r
 *  -f <file_name_to_open>
 *  -utf-8
 *  -utf-16
 *  -utf-32
 */

int main(int argc, char **argv) {

    string fileName;
    sf::String (*encoding)(std::__1::wstring::iterator begin, 
                           std::__1::wstring::iterator end) = sf::String::fromUtf8;
    bool readOnly = false;
    bool highlight = true;

    if (cmdFlagExists(argv, argv + argc, "-f")) {
        fileName = getCmdFlag(argv, argv + argc, "-f");

        if (cmdFlagExists(argv, argv + argc, "-r"))
            readOnly = true;
        if (cmdFlagExists(argv, argv + argc, "-no_highlight"))
            highlight = false;

        if (cmdFlagExists(argv, argv + argc, "-utf-8"))
            encoding = sf::String::fromUtf8;
        else if (cmdFlagExists(argv, argv + argc, "-utf-16"))
            encoding = sf::String::fromUtf16;
        else if (cmdFlagExists(argv, argv + argc, "-utf-32"))
            encoding = sf::String::fromUtf32;
    } else {
        fileName = "resources/about.txt";
        readOnly = true;
        highlight = false;
    }

    DocumentEditor documentEditor(encoding, highlight);
    try {
        documentEditor.open(fileName);
    } catch (const char *e) {
        cerr << e << endl;
        exit(EXIT_FAILURE);
    }

    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), fileName);

    sf::Color backgroundColor = sf::Color(30, 30, 30, 255);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width,
                                          event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down)
                    documentEditor.scrollDown();
                if (event.key.code == sf::Keyboard::Up)
                    documentEditor.scrollUp();
                if (event.key.code == sf::Keyboard::Left)
                    documentEditor.moveLeft();
                if (event.key.code == sf::Keyboard::Right)
                    documentEditor.moveRight();
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            if (!readOnly && event.type == sf::Event::TextEntered)
                documentEditor.typeOn(event);
            if (!readOnly && (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                try {
                    documentEditor.save();
                } catch (const char *e) {
                    cerr << e << endl;
                }
        }
        window.clear(backgroundColor);
        documentEditor.view(window);
        window.display();
    }

    exit(EXIT_SUCCESS);
}

char *getCmdFlag(char **begin, char **end, const std::string &flag) {
    char **itr = std::find(begin, end, flag);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmdFlagExists(char **begin, char **end, const std::string &flag) {
    return std::find(begin, end, flag) != end;
}
