import QtQuick 2.0
import "."
Rectangle {
    property int activePageCount: 0
    property int animTime: 100

    //model is a list of {"name":"somename", "url":"file:///some/url/mainfile.qml"}
    //function used to add to model A) to enforce scheme B) to allow Qt.resolveUrl in url assignments

    color: "#eee"
    function addExample(name, desc, url)
    {
        //pour creer un list model on peut insert des tuples ainsi
        myModel.append({
                           "name":name,
                           "description":desc,
                           "url":url,
                       })
    }

    // The container rectangle here is used to give a nice "feel" when
    // transitioning into an example.
    Rectangle {
        anchors.fill: parent
        color: "black"
        ListView {
            id: launcherList
            clip: true
            delegate: LauncherDelegate{
                onClicked: {
                    //createobject E Component
                    var page = pageComponent.createObject(pageContainer, { exampleUrl: url, animTime : animTime})
                    page.show()
                }

            }
            model: ListModel {
                id:myModel
            }
            anchors.fill: parent
            enabled: opacity == 1.0

        }
    }
    LaucherComponent{
        id:pageComponent
    }

        Item {
            id: pageContainer
            implicitWidth:  parent.width
            implicitHeight:   parent.height - bar.height
        }

        Rectangle {
            id: bar
            visible: height > 0
            anchors.bottom: parent.bottom
            width: parent.width
            height: activePageCount > 0 ? 40 : 0

            Behavior on height {
                NumberAnimation {
                    duration: 300
                }
            }

            Rectangle {
                height: 1
                color: "#ccc"
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
            }

            Rectangle {
                height: 1
                color: "#fff"
                anchors.top: parent.top
                anchors.topMargin: 1
                anchors.left: parent.left
                anchors.right: parent.right
            }

            gradient: Gradient {
                GradientStop { position: 0 ; color: "#eee" }
                GradientStop { position: 1 ; color: "#ccc" }
            }

            Image {
                id: back
                source: "../images/back.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 2
                anchors.left: parent.left
                anchors.leftMargin: 16

                MouseArea {
                    id: mouse
                    hoverEnabled: true
                    anchors.centerIn: parent
                    width: 38
                    height: 31
                    anchors.verticalCenterOffset: -1
                    enabled: activePageCount > 0
                    onClicked: {
                        pageContainer.children[pageContainer.children.length - 1].exit()
                    }
                    Rectangle {
                        anchors.fill: parent
                        opacity: mouse.pressed ? 1 : 0
                        Behavior on opacity { NumberAnimation{ duration: 100 }}
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: "#22000000" }
                            GradientStop { position: 0.2 ; color: "#11000000" }
                        }
                        border.color: "darkgray"
                        antialiasing: true
                        radius: 4
                    }
                }
            }
        }

}
