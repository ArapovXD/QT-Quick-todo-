import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import "Pages"

Window {
    id: window_
    minimumWidth: 330
    minimumHeight: 550
    width: 480
    height: 640
    visible: true

    property bool isAuthPage: true

    AuthPage{
        anchors.fill: parent
        visible: window_.isAuthPage
    }

    AppPage{
        anchors.fill: parent
        visible: !window_.isAuthPage
    }


    Connections {
        target: auth
        onUserSignedIn: {
            todoModel.initData(auth.getUserEmail())
            window_.isAuthPage = false
        }
    }

}
