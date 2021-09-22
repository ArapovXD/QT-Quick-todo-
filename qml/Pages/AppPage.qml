import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: root_

    Column {
        id: mainContent_
        anchors.margins: 10
        anchors.fill: parent
        spacing: 10

        Dialog {
            id: dialog_
            width: parent.width
            height: parent.height / 7
            visible: false
            Column {
                width: parent.width
                height: parent.height
                TextField {
                    id: addText_
                    width: parent.width
                    height: parent.height / 1.5
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: "Add todo..."
                }

                Row {
                    id: dialogButtons_
                    height: parent.height / 3
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 10

                    function handleClose(){
                        addText_.text = ""
                        dialog_.visible = false
                    }

                    Rectangle {
                        width: dialog_.width / 3
                        height: parent.height
                        color: "green"
                        Text {
                            anchors.centerIn: parent
                            text: "Add"
                            color: "white"
                            font.pixelSize: 15
                        }

                        MouseArea {
                            function handleAdd() {
                                todoModel.addTodo(auth.getUserEmail(), addText_.text)
                                dialogButtons_.handleClose()
                            }

                            anchors.fill: parent
                            onClicked: handleAdd()
                        }
                    }

                    Rectangle {
                        width: dialog_.width / 3
                        height: parent.height
                        color: "gray"
                        Text {
                            anchors.centerIn: parent
                            text: "Cancel"
                            color: "white"
                            font.pixelSize: 15
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: dialogButtons_.handleClose()
                        }
                    }
                }

            }
        }

        ScrollView {
            width: parent.width
            height: parent.height * 0.9

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            clip: true

            ListView {
                id: contentView_

                width: parent.width
                height: parent.height
                spacing: 10

                model: todoModel

                delegate: Row {
                    width: contentView_.width
                    height: mainContent_.width / 10

                    Rectangle {
                        id: editBtn_

                        width: parent.width / 6
                        height: parent.height
                        Text {
                            id: editBtnText_
                            text: "Edit"
                            anchors.centerIn: parent
                            font.pixelSize: 20
                        }

                        MouseArea {
                            id: editBtnArea_
                            anchors.fill: parent
                        }
                    }

                    Rectangle {
                        id: todoContent_
                        width: parent.width * 2 / 3
                        height: parent.height

                        Text {
                            id: todoContentText_
                            text: model.text
                            anchors.centerIn: parent
                            font.pixelSize: 20
                        }

                        MouseArea {
                            id: todoContentArea_
                            anchors.fill: parent
                        }
                    }

                    Rectangle {
                        id: deleteBtn_

                        width: parent.width / 6
                        height: parent.height
                        Text {
                            id: deleteBtn_Text_
                            text: "Delete"
                            anchors.centerIn: parent
                            font.pixelSize: 20
                        }

                        MouseArea {
                            id: deleteBtnArea_
                            anchors.fill: parent
                        }
                    }
                }


            }
        }

        Rectangle {
            id: addBtn_
            width: parent.width / 2
            height: parent.height * 0.08
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 10
            color: "green"

            Text {
                id: addBtnText_
                text: "Add ToDo"
                anchors.centerIn: parent
                font.pixelSize: 25
                color: "white"
            }


            MouseArea {
                id: addBtnArea_
                anchors.fill: parent
                onClicked: dialog_.visible = true
            }


        }

    }
}
