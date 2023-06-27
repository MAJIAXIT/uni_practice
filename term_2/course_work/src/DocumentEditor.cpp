#include "DocumentEditor.h"

DocumentEditor::DocumentEditor(
    sf::String (*_encoding)(std::__1::wstring::iterator begin,
                            std::__1::wstring::iterator end),
    bool _highlight) {
    static sf::Font font;
    if (!font.loadFromFile("resources/FiraCode-Retina.ttf"))
        throw "DocumentEditor::DocumentEditor : Error while loading fonts\n";
    highlight = _highlight;
    encoding = _encoding;
}

void DocumentEditor::open(std::string _path) {
    std::wfstream file(_path);
    if (!file) {
        file.open(_path, std::fstream::out);
        if (!file)
            throw "DocumentEditor::open : Cant open file.";
    }

    path = _path;
    edited = false;

    std::wstring line;
    while (getline(file, line)) {
        TextBox *tb = new TextBox(CHARACTER_SIZE, line, encoding, highlight);
        content.push_back(tb);
        cursor.linesCount++;
    }

    if (cursor.linesCount == 0) {
        TextBox *tb = new TextBox(CHARACTER_SIZE, L"", encoding, highlight);
        content.push_back(tb);
        cursor.linesCount++;
    }

    file.close();
}

void DocumentEditor::save() {
    if (!edited)
        return;

    std::wofstream file(path);
    if (!file)
        throw "DocumentEditor::save : Cant open file.";

    static std::locale loc("ru_RU.UTF-8");

    file.imbue(loc);

    for (int i = 0; i < cursor.linesCount; i++) {
        file << content[i]->getString().c_str() << std::endl;
    }

    if (!file.good())
        throw "DocumentEditor::save : Cant save file data.";

    file.close();
    edited = false;
}

void DocumentEditor::scrollUp(int lines) {
    cursor.moveUp(lines);
    if (cursor.getCharPos() > content[cursor.getLinePos()]->getTextLen())
        cursor.setCharPos(content[cursor.getLinePos()]->getTextLen());
}

void DocumentEditor::scrollDown(int lines) {
    cursor.moveDown(lines);
    if (cursor.getCharPos() > content[cursor.getLinePos()]->getTextLen())
        cursor.setCharPos(content[cursor.getLinePos()]->getTextLen());
}

void DocumentEditor::moveLeft(int chs) {
    int prevLineLenOrZero =
        cursor.getLinePos() == 0 ? 0 : cursor.getLinePos() - 1;
    if (!(cursor.getCharPos() == 0 && cursor.getLinePos() == 0))
        cursor.moveLeft(content[prevLineLenOrZero]->getTextLen(), chs);
}

void DocumentEditor::moveRight(int chs) {
    cursor.moveRight(content[cursor.getLinePos()]->getTextLen(), chs);
}

void DocumentEditor::typeOn(sf::Event event) {
    edited = true;
    switch (content[cursor.getLinePos()]->typeOn(event, cursor.getCharPos())) {
    case INS_CHAR:
        cursor.moveRight(content[cursor.getLinePos()]->getTextLen());
        break;
    case DELETE_CHAR:
        cursor.moveLeft(content[cursor.getLinePos()]->getTextLen());
        break;
    case DELETE_LINE:
        if (cursor.getLinePos() != 0) {
            cursor.setCharPos(content[cursor.getLinePos() - 1]->getTextLen());
            content[cursor.getLinePos() - 1]->insert(
                content[cursor.getLinePos() - 1]->getTextLen(),
                content[cursor.getLinePos()]->getString());

            content.erase(content.begin() + cursor.getLinePos());
            cursor.linesCount--;
            scrollUp();
        }
        break;
    case NEW_LINE:
        TextBox *tb;
        tb = new TextBox(*content[cursor.getLinePos()]);
        tb->erase(0, cursor.getCharPos());
        content[cursor.getLinePos()]->erase(
            cursor.getCharPos(), content[cursor.getLinePos()]->getTextLen());

        content.insert(content.begin() + cursor.getLinePos() + 1, tb);
        cursor.linesCount++;
        scrollDown();
        cursor.setCharPos(0);
        break;
    }
}

void DocumentEditor::view(sf::RenderWindow &window) {
    cursor.linesOnScreen = window.getSize().y / 
                           (CHARACTER_SIZE + LINE_SPACING);

    for (int lineNum = cursor.firstLine; 
             lineNum < cursor.firstLine + cursor.linesOnScreen &&
             lineNum < cursor.linesCount; 
             lineNum++) {
        content[lineNum]->setPosition(lineNum - cursor.firstLine, lineNum);
        content[lineNum]->drawTo(window);
    }

    float xpos = content[cursor.getLinePos()]->getText()
                    .findCharacterPos(cursor.getCharPos()).x;
    float ypos = content[cursor.getLinePos()]->getText()
                    .findCharacterPos(cursor.getCharPos()).y;
    
    cursor.drawTo(window, xpos, ypos);
}

DocumentEditor::~DocumentEditor() {
    for (auto i : content)
        delete i;
}
