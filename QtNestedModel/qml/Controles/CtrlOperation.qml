import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "."

Item {

    Text{
       text:"operation"
    }

    TextInput{
        id:name
    }

    ColumnLayout{
        ComboBox{
            id :signal1
        }
        ComboBox{
            id :type
            model: [
                "*"         ,
                "/"         ,
                "+"         ,
                "-"         ,
                "pow"       ,
                "%"         ,
                "T"         ,
                "m"         ,
                "M"         ,
                "_"         ,
                "exp"       ,
                "cos"       ,
                "sin"       ,
                "vibe"      ,
                "sigmo"     ,
                "triangle"  ,
                "rectif"    ,
                "fade"      ,
            ]
        }
        ComboBox{
            id :signal2
        }
    }



}
