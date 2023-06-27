#include "TextBox.h"

TextBox::TextBox(int charSize, std::wstring str,
                 sf::String (*encoding)(std::__1::wstring::iterator begin,
                                        std::__1::wstring::iterator end),
                 bool _highlight) {
    static sf::Font font;
    if(!font.loadFromFile("resources/FiraCode-Retina.ttf")) {
        std::cerr << "TextBox::TextBox : Error while loading font. Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }
    highlight = _highlight;

    textBox.setFont(font);
    textBox.setCharacterSize(charSize);
    if (!highlight)
        textBox.setFillColor(sf::Color::White);
    lnNum.setFont(font);
    lnNum.setFillColor(sf::Color::Yellow);
    lnNum.setCharacterSize(charSize);

    text = encoding(begin(str), end(str));
}

TextBox::TextBox(TextBox &from) {
    highlight = from.highlight;
    textBox = from.textBox;
    lnNum = from.lnNum;
    text = from.text;
}

int TextBox::inputLogic(wchar_t charTyped, int chPos) {
    int ans = 0;
    if (charTyped != DELETE_KEY && 
        charTyped != ENTER_KEY) {
        text.insert(chPos, static_cast<sf::String>(charTyped));
        ans = INS_CHAR;
    } else if (charTyped == DELETE_KEY) {
        ans = deleteChar(chPos);
    } else if (charTyped == ENTER_KEY) {
        ans = NEW_LINE;
    }
    return ans;
}

int TextBox::deleteChar(int chPos) {
    if (chPos > 0 && getTextLen() > 0) {
        text.erase(chPos - 1, 1);
        return DELETE_CHAR;
    } else
        return DELETE_LINE;
}

void TextBox::erase(size_t beg, size_t end) {
    text.erase(beg, end);
}

void TextBox::insert(int pos, std::wstring str) {  
    text.insert(pos, str);
}

std::wstring TextBox::getString() { return text.toWideString(); }


/* FText class allows to color any number 
 * of characters after %\d, where \d is digit from the 
 * FText::getColorForChar function
 * %0 - White
 * %1 - Cyan
 * %2 - Violet
 * $3 - Blue
 */
void TextBox::colorText() {
    std::wstring coloredString = text;
    if (!highlight) {
        textBox.setString(coloredString);
        return;
    }

    static std::wregex keywords(L"\\b((auto)|(double)|(int)|(struct)|(break)|(else)|(long)|(switch)|(case)|(enum)|(register)|(typedef)|(char)|(extern)|(return)|(union)|(continue)|(for)|(signed)|(void)|(do)|(if)|(static)|(while)|(default)|(sizeof)|(goto)|(volatile)|(const)(float)|(short)|(unsigned))\\b");
    static std::wregex numbers(L"[0-9]");
    static std::wregex spec(
        L"(^|\\s)((#define)|(#ifndef)|(#endif)|(#include))\\b");
    static std::wregex constants(L"(\"(.*?)\")");

    coloredString = std::regex_replace(coloredString, std::wregex(L"%"), L"%%");
    coloredString = std::regex_replace(coloredString, numbers, L"%2$&%0");
    coloredString = std::regex_replace(coloredString, spec, L"%3$&%0");
    coloredString = std::regex_replace(coloredString, keywords, L"%1$&%0");

    if (std::regex_search(coloredString, constants)) {
        bool work = false;
        int strSize = coloredString.size();
        for (int i = 0; i < strSize; i++) {
            if (coloredString[i] == '"' && work)
                work = false;
            if (coloredString[i] == '"')
                work = true;
            if (work && coloredString[i] == '%' &&
                isnumber(coloredString[i + 1])) {
                coloredString.erase(i, 2);
                strSize -= 2;
            }
        }
        coloredString = std::regex_replace(coloredString, constants, L"%2$&%0");
    }
    textBox.setString(coloredString);
}

sf::FText TextBox::getText() {
    colorText();
    return textBox;
}

void TextBox::setPosition(int lnNumOnScr, int lineNum) { 
    std::stringstream lnNumss;
    lnNumss << std::setw(4) << std::to_string(lineNum + 1);
    lnNum.setString(lnNumss.str());
    lnNum.setPosition(0, (CHARACTER_SIZE + LINE_SPACING) * lnNumOnScr);
    textBox.setPosition(XOFFSET, (CHARACTER_SIZE + LINE_SPACING) * lnNumOnScr); 
}

void TextBox::drawTo(sf::RenderWindow &window) {
    colorText();
    window.draw(lnNum);
    window.draw(textBox); 
}

int TextBox::typeOn(sf::Event input, int chPos) {
    wchar_t charTyped = input.text.unicode;
    return inputLogic(charTyped, chPos);
}

int TextBox::getTextLen() { return text.getSize(); }
