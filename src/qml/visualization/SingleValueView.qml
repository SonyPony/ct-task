import QtQuick 2.0

Item {
    id: component

    property color labelBackgroundColor
    property color valueBackgroundColor
    property alias label: label
    property alias value: value
    property font font

    width: value.x + value.width + label.anchors.leftMargin

    Text {
        id: label

        z: 1

        font.family: component.font.family
        font.pixelSize: component.height * 0.65

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: font.pixelSize / 2.
    }

    Text {
        id: value

        z: 1

        font: label.font

        anchors.top: label.top
        anchors.left: label.right
        anchors.leftMargin: font.pixelSize
    }

    Canvas {
        id: background

        opacity: 0.8

        anchors.fill: parent

        onPaint: {
            var ctx = getContext('2d');

            // draw value background
            ctx.fillStyle = component.valueBackgroundColor;
            ctx.fillRect(0, 0, background.width, background.height);

            // draw label background
            ctx.fillStyle = component.labelBackgroundColor;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(label.x + label.width, 0);
            ctx.lineTo(label.x + label.width + value.anchors.leftMargin, background.height);
            ctx.lineTo(0, background.height);
            ctx.lineTo(0, 0)
            ctx.fill();
            ctx.closePath()
        }
    }
}
