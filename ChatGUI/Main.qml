import QtQuick
import QtQuick.Controls
import Chat 1.0
import QtQuick.Layouts

Window {
    width: 400
    height: 600
    visible: true
    title: qsTr("Chat App")

    MessageModel
    {
        id: msgModel

        function send()
        {
            sendMessage()
            messageInput.clear()
        }

    }

    ColumnLayout
    {
        anchors.fill: parent;
        spacing: 8

        ListView
        {
            id: messageList
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            Layout.topMargin: 10;

            model: msgModel
            clip: true

            onCountChanged:
            {
                Qt.callLater(()=> messageList.positionViewAtEnd())
            }


            delegate:Rectangle
            {
                height: messageText.implicitHeight +20
                width: parent.width
                color: "transparent"

                Rectangle
                {
                    height: parent.height;
                    width: parent.width -40;
                    color: display.startsWith("ME:") ? "#d1eaff" : "#fce4ec"
                    radius: 10
                    anchors.right: display.startsWith("ME:") ? parent.right: undefined
                    anchors.left: !display.startsWith("ME:") ? parent.left: undefined

                    Text {
                        id: messageText
                            text: display.substring(3)
                            anchors
                            {
                                fill: parent;
                                margins: 10
                            }
                            wrapMode: Text.Wrap
                        }

                }


            }
        }

        RowLayout
        {
            Layout.fillWidth: true
            Layout.preferredHeight: 40;
            Layout.margins: 10

            TextField
            {
                id: messageInput
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                text: msgModel.currentMessage
                onTextChanged: msgModel.currentMessage = text
                Keys.onReturnPressed: msgModel.send()
                placeholderText: "Type a message here..."
                font.pixelSize: 16
            }

            RoundButton
            {
                id: sendButton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                onClicked: msgModel.send()
                palette.button: pressed ? "#218838"        // Darker green for pressed
                                : hovered? "#28a745"   // Medium green for hover
                                : "#34c759"   // Bright green default
                icon.source: "qrc:/qt/qml/ChatGUI/icons/send.png"
            }

        }





    }




}
