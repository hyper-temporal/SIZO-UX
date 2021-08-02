import QtQuick 2.7
import QtQuick.Controls 2.2
import "."

Item {

    TextInput{
        id:name
    }
    ComboBox{
        id :type
        model: [
            "reverb"    ,
            "limiter"   ,
            "filtre"    ,
            "distortion",
            "generic"   ,
        ]

    }
}
