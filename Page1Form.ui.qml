import QtQuick 2.14
import QtQuick.Controls 2.14

Page {
    width: 800
    height: 400
    property alias powerButton: powerButton
    property alias kpButton: kpButton
    property alias currentPowerLabel: currentPowerLabel
    property alias currentCadenceLabel: currentCadenceLabel
    property alias targetPowerLabel: targetPowerLabel
    property alias targetKpLabel: targetKpLabel
    property alias inclots: inclots
    property alias inc: inc
    property alias dec: dec
    property alias declots: declots

    header: Label {
        text: qsTr("Controls")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10

        Button {
            id: kpButton
            x: 340
            y: 30
            width: 200
            text: qsTr("Target Kp")
        }

        Button {
            id: powerButton
            x: 575
            y: 30
            width: 200
            text: qsTr("Target Power")
        }

        Label {
            id: label4
            x: 247
            y: 30
            width: 87
            height: 47
            text: qsTr("Mode:")
            font.pointSize: 21
        }
    }

    Button {
        id: declots
        x: 15
        y: 60
        width: 159
        height: 195
        text: qsTr("Dec Lots")
    }

    Button {
        id: dec
        x: 219
        y: 60
        width: 159
        height: 195
        text: qsTr("Dec")
    }

    Button {
        id: inc
        x: 421
        y: 60
        width: 159
        height: 195
        text: qsTr("Inc")
    }

    Button {
        id: inclots
        x: 618
        y: 60
        width: 159
        height: 195
        text: qsTr("Inc Lots")
    }

    Label {
        id: currentPowerLabel
        x: 15
        y: 289
        width: 159
        height: 41
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: currentCadenceLabel
        x: 219
        y: 289
        width: 159
        height: 41
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: targetPowerLabel
        x: 421
        y: 289
        width: 159
        height: 41
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: targetKpLabel
        x: 618
        y: 289
        width: 159
        height: 41
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label
        x: 76
        y: 264
        text: qsTr("Power")
    }

    Label {
        id: label1
        x: 270
        y: 264
        text: qsTr("Cadence")
    }

    Label {
        id: label2
        x: 455
        y: 264
        text: qsTr("Target Power")
    }

    Label {
        id: label3
        x: 665
        y: 264
        text: qsTr("Target Kp")
    }
}
