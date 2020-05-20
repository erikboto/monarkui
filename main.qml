import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.VirtualKeyboard 2.14
import se.unixshell.Monark 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480
    title: qsTr("Tabs")

    MqttClient {
        id: mqtt

        onCurrentPowerChanged: page1.currentPowerLabel.text = mqtt.currentPower
        onCurrentCadenceChanged: page1.currentCadenceLabel.text = mqtt.currentCadence
        onTargetPowerChanged: page1.targetPowerLabel.text = mqtt.targetPower
        onTargetKpChanged: page1.targetKpLabel.text = mqtt.targetKp

        onModeChanged: console.log("new mode" + mode)
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
            id: page1
            dec.onClicked: mqtt.decGear()
            declots.onClicked: mqtt.decGearLots()
            inc.onClicked: mqtt.incGear()
            inclots.onClicked: mqtt.incGearLots()

            powerButton.font.bold: mqtt.mode == MqttClient.POWER
            kpButton.font.bold: mqtt.mode == MqttClient.KP

            kpButton.onClicked: mqtt.setMode(MqttClient.KP);
            powerButton.onClicked: mqtt.setMode(MqttClient.POWER);
        }
    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex

//        TabButton {
//            text: qsTr("Page 1")
//        }
//        TabButton {
//            text: qsTr("Page 2")
//        }
//    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
