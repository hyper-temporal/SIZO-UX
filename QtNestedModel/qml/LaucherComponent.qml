import QtQuick 2.0

Component {
    id: pageComponent

    Rectangle {
        id: page
        clip: true
        property url exampleUrl
        property int animTime
        anchors.fill: parent


        color: "white"
        MouseArea{
            //Eats mouse events
            anchors.fill: parent
        }
        Loader{
            focus: true
            source: parent.exampleUrl
            anchors.fill: parent

        }

        x: -width

        function show() {
            showAnim.start()
        }

        function exit() {
            exitAnim.start()
        }

        ParallelAnimation {
            id: showAnim
            ScriptAction {
                script: activePageCount++
            }
            NumberAnimation {
                target: launcherList
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: animTime
            }
            NumberAnimation {
                target: launcherList
                property: "scale"
                from: 1.0
                to: 0.0
                duration: animTime
            }
            NumberAnimation {
                target: page
                property: "x"
                from: -page.width
                to: 0
                duration: animTime
            }
        }
        SequentialAnimation {
            id: exitAnim

            ScriptAction {
                script: activePageCount--
            }

            ParallelAnimation {
                NumberAnimation {
                    target: launcherList
                    property: "opacity"
                    from: 0.0
                    to: 1.0
                    duration: animTime
                }
                NumberAnimation {
                    target: launcherList
                    property: "scale"
                    from: 0.0
                    to: 1.0
                    duration: animTime
                }
                NumberAnimation {
                    target: page
                    property: "x"
                    from: 0
                    to: -page.width
                    duration: animTime
                }
            }

            ScriptAction {
                script: page.destroy()
            }
        }
    }
}
