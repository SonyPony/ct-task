import QtQuick 2.0
import "../controls" as Controls

Item {
    id: component

    property Component label
    property color labelBackgroundColor
    property color valueBackgroundColor

    property string valueUnit: ""
    property real valueReal: 0
    property alias value: valueText

    property string historyUnit: ""
    property real historyReal: 0
    property alias history: historyText

    property font font

    property real barWidth: 0
    readonly property real barHeight: component.height / 3.2
    readonly property real barOffset: barHeight * 0.3
    readonly property real labelWidth: label.width + label.x + background.height / 2.5

    width: barWidth + labelWidth
    clip: false

    onValueChanged: background.requestPaint()
    onHistoryChanged: background.requestPaint()

    Loader {
        id: label

        z: 1
        height: component.height * 0.8
        sourceComponent: component.label

        anchors.left: parent.left
        anchors.leftMargin: (component.height - label.height) / 2.
        anchors.verticalCenter: parent.verticalCenter
    }

    Item {
        id: valueContainer

        z: 1
        height: component.barHeight
        width: (valueReal < historyReal)
        ?component.barWidth * (valueReal / historyReal)
        :component.barWidth

        anchors.left: parent.left
        anchors.leftMargin: component.labelWidth
        anchors.bottom: historyContainer.top
        anchors.bottomMargin: component.barOffset

        Controls.TextWithBackground {
            id: valueText

            text: Number(component.valueReal.toFixed(1)) + component.valueUnit
            font.family: component.font.family
            font.pixelSize: parent.height * 0.8

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: font.pixelSize / 2.
        }
    }

    Item {
        id: historyContainer

        z: 1
        height: component.barHeight
        width: (valueReal < historyReal)
        ?component.barWidth
        :component.barWidth * (historyReal / valueReal)

        anchors.left: parent.left
        anchors.leftMargin: component.labelWidth
        anchors.bottom: parent.bottom

        Controls.TextWithBackground {
            id: historyText

            text: Number(component.historyReal.toFixed(1)) + component.historyUnit
            font: valueText.font

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: font.pixelSize / 2.
        }
    }

    Canvas {
        id: background

        opacity: 0.8
        anchors.fill: parent
        clip: false

        onPaint: {
            var labelWidth = component.labelWidth
            var barHeight = component.barHeight
            var width = component.width
            var height = component.height

            var ctx = background.getContext('2d')
            ctx.fillStyle = historyText.backgroundColor
            ctx.fillRect(0, height - barHeight, labelWidth + historyContainer.width, barHeight)
            ctx.fillStyle = valueText.backgroundColor
            ctx.fillRect(0, height - barHeight * 2 - component.barOffset, labelWidth + valueContainer.width, barHeight)

            ctx.fillStyle = component.labelBackgroundColor
            ctx.beginPath()
            ctx.moveTo(0, 0)
            ctx.lineTo(labelWidth - height / 2.5, 0)
            ctx.lineTo(labelWidth, height)
            ctx.lineTo(0, height)
            ctx.lineTo(0, 0)
            ctx.fill()
            ctx.closePath()
        }
    }
}
