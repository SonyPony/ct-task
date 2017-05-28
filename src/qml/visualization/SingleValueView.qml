import QtQuick 2.0
import "../controls" as Controls

Item {
    id: component

    property alias label: labelText
    property alias value: valueText
    property real valueReal: 0
    property string unit: ""
    property font font

    width: valueText.x + valueText.width + labelText.anchors.leftMargin

    Controls.TextWithBackground {
        id: labelText

        z: 1

        font.family: component.font.family
        font.pixelSize: component.height * 0.65

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: font.pixelSize / 2.
    }

    Controls.TextWithBackground {
        id: valueText

        z: 1
        text: Number(component.valueReal.toFixed(1)) + component.unit

        font: labelText.font

        anchors.top: labelText.top
        anchors.left: labelText.right
        anchors.leftMargin: font.pixelSize
    }

    Canvas {
        id: background

        opacity: 0.8

        anchors.fill: parent

        onPaint: {
            var ctx = getContext('2d')

            // draw value background
            ctx.fillStyle = component.value.backgroundColor
            ctx.fillRect(0, 0, background.width, background.height)

            // draw label background
            ctx.fillStyle = component.label.backgroundColor
            ctx.beginPath()
            ctx.moveTo(0, 0)
            ctx.lineTo(labelText.x + labelText.width, 0)
            ctx.lineTo(labelText.x + labelText.width + valueText.anchors.leftMargin, background.height)
            ctx.lineTo(0, background.height)
            ctx.lineTo(0, 0)
            ctx.fill()
            ctx.closePath()
        }
    }
}
