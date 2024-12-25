import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    width: 800
    height: 200
    color: "#333333"

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 40
            color: "#404040"

            Label {
                id: lineNumbers
                objectName: "lineNumbers"
                anchors.fill: parent
                anchors.rightMargin: 5
                text: {
                    var lines = textArea.text.split('\n').length
                    var numbers = []
                    for (var i = 1; i <= lines; i++) {
                        numbers.push(i)
                    }
                    return numbers.join('\n')
                }
                font.family: "Fira Code"
                font.pixelSize: 18
                color: "#808080"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignTop
            }
        }

        ScrollView {
            id: scrollView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            TextArea {
                id: textArea
                objectName: "textArea"
                width: scrollView.width
                text: "#include \"mainwindow.h\"\n" +
                "\n" +
                "#include <QApplication>\n" +
                "\n" +
                "int main(int argc, char *argv[])\n" +
                "{\n" +
                "    QApplication a(argc, argv);\n" +
                "    MainWindow w;\n" +
                "    w.show();\n" +
                "    return a.exec();\n" +
                "}\n"
                font.family: "Fira Code"
                font.pixelSize: 18
                color: "white"
                background: Rectangle {
                    color: "#333333"
                }
                wrapMode: TextArea.NoWrap

                onTextChanged: {
                    var lines = textArea.text.split('\n').length;
                    var numbers = [];
                    for (var i = 1; i <= lines; i++) {
                        numbers.push(i);
                    }
                    lineNumbers.text = numbers.join('\n');
                }
            }
        }
    }
}
