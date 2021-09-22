import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.15

Rectangle {
    id: root_
    color: "#e5fdff"

    Column {
        id: content_
        width: root_.width * 0.7
        height: root_.height / 1.7
        spacing: 10
        anchors.centerIn: parent

        property bool loginSelected: true
        property var colors: ["#e3e8e8", "#909191"]


        Row {
            id: authNavigate_
            width: parent.width
            height: parent.height / 6

            function handleNavClick(isLoginBtn){
                if (isLoginBtn && content_.loginSelected) return
                if (!isLoginBtn && !content_.loginSelected) return
                content_.loginSelected = !content_.loginSelected
            }

            Rectangle {
                id: loginNavigate
                width: parent.width / 2
                height: parent.height

                Text {
                    id: loginNavigateTxt_
                    text: "Log In"
                    anchors.centerIn: parent
                    font.pixelSize: 25
                }

                Rectangle {
                    id: loginNavigateBorder_
                    width: parent.width
                    height: 2
                    color: content_.colors[Number(content_.loginSelected)]
                    anchors.bottom: parent.bottom
                }

                MouseArea {
                    id: loginNavigateArea_
                    anchors.fill: parent
                    onClicked: authNavigate_.handleNavClick(1)
                }
            }

            Rectangle {
                id: signupNavigate
                width: parent.width / 2
                height: parent.height
                Text {
                    id: signUpNavigateTxt_
                    text: "Sign Up"
                    anchors.centerIn: parent
                    font.pixelSize: 25
                }

                Rectangle {
                    id: signUpNavigateBorder_
                    width: parent.width
                    height: 2
                    color: content_.colors[Number(!content_.loginSelected)]
                    anchors.bottom: parent.bottom
                }

                MouseArea {
                    id: signUpNavigateArea_
                    anchors.fill: parent
                    onClicked: authNavigate_.handleNavClick(0)
                }
            }
        }

        Column {
            id: login_
            width: parent.width
            visible: content_.loginSelected
            spacing: 10

            TextField {
                id: emailInput_
                anchors.left: parent.left
                anchors.right: parent.right
                font.pixelSize: 20
                placeholderText: "Email"
                wrapMode: TextField.WordWrap
                focus: false
            }

            TextField {
                id: passwordInput_
                anchors.left: parent.left
                anchors.right: parent.right
                font.pixelSize: 20
                placeholderText: "Password"
                wrapMode: TextField.WordWrap
            }

            Rectangle {
                id: loginBtn
                height: content_.height / 10
                width: parent.width / 2
                Text {
                    text: "Log In"
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 2
                }

                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    id: loginBtnArea
                    anchors.fill: parent
                    onClicked: auth.signUserIn(emailInput_.text, passwordInput_.text)
                }
            }
        }

        Column {
            id: signup_
            width: parent.width
            visible: !content_.loginSelected
            spacing: 10

            TextField {
                id: emailInput2_
                anchors.left: parent.left
                anchors.right: parent.right
                font.pixelSize: 20
                placeholderText: "Email"
                wrapMode: TextField.WordWrap
                focus: false
            }

            TextField {
                id: passwordInput2_
                anchors.left: parent.left
                anchors.right: parent.right
                font.pixelSize: 20
                placeholderText: "Password"
                wrapMode: TextField.WordWrap
            }

            TextField {
                id: confirmPasswordInput2_
                anchors.left: parent.left
                anchors.right: parent.right
                font.pixelSize: 20
                placeholderText: "Confirm password"
                wrapMode: TextField.WordWrap
            }

            Rectangle {
                id: signupBtn
                height: content_.height / 10
                width: parent.width / 2
                Text {
                    text: "Sign Up"
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 2
                }

                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    id: signUpBtnArea
                    anchors.fill: parent
                    onClicked: auth.signUserUp(emailInput2_.text, passwordInput2_.text)
                    focus: true
                }
            }
        }
    }
}
