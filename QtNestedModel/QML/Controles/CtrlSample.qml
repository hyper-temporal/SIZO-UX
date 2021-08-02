import QtQuick 2.0

Item {
    property string name: ""
    property string path: ""
    TextInput{
        text: name
    }
    TextInput{
        text:path
    }
}
