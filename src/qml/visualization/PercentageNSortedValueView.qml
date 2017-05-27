import QtQuick 2.7

Rectangle {
    id: component

    property int valuesCount: 2
    property real valueLimit: 0
    readonly property real offset: 10
    readonly property real barHeight: (component.height - (valuesCount - 1) * offset) / valuesCount
    property font font

    color: "red"

    FontMetrics {
        id: fm
        font: component.font
    }

    QtObject {
        id: internal

        property var data: new Array
        property int model: 0
        readonly property real fontPixelSize: component.barHeight * 0.8
        property real pixelsPerPercent: component.width / 100.
        readonly property real textOffset: internal.fontPixelSize / 3.

        onFontPixelSizeChanged: {
            component.font.pixelSize = fontPixelSize
            checkMinBarWidth()
        }
        onDataChanged: checkMinBarWidth()

        function checkMinBarWidth() {
            var offsets = internal.textOffset * 2
            var maximumTextWidth = 0
            var maximumTextWidthValue, text, data, textWidth
            var valuesCount = component.valuesCount
            var dataLen = internal.data.length

            var startIndex = (valuesCount >= dataLen) ?0 :dataLen - valuesCount
            internal.pixelsPerPercent = component.width / 100.

            for(var i = startIndex; i < dataLen; i++) {
                data = internal.data[i]
                text = "%1 %2%"
                .arg(data["label"])
                .arg(Number(data["value"].toFixed(2)))
                textWidth = offsets + fm.boundingRect(text).width

                if(textWidth > data["value"] * internal.pixelsPerPercent) {
                    maximumTextWidth = Math.max(textWidth, maximumTextWidth)
                    maximumTextWidthValue = data["value"]
                    internal.pixelsPerPercent = maximumTextWidth / maximumTextWidthValue
                }
            }
        }

        function compareItems(valueItemA, valueItemB) {
            if(valueItemA["value"] < valueItemB["value"])
                return -1
            else if(valueItemA["value"] > valueItemB["value"])
                return 1
            return 0
        }
    }

    Column {
        anchors.fill: parent
        spacing: offset
        rotation: 180
        Repeater {
            id: repeater

            model: internal.model

            delegate: Rectangle {
                property int index: (repeater.model == component.valuesCount)
                                    ?internal.data.length - component.valuesCount + modelData
                                    :modelData

                rotation: 180
                color: internal.data[index]["color"]
                width: internal.data[index]["value"] * internal.pixelsPerPercent
                height: component.barHeight

                anchors.right: parent.right

                Text {
                    id: label

                    text: internal.data[index]["label"]

                    font: component.font

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: internal.textOffset
                }

                Text {
                    text: Number(internal.data[index]["value"].toFixed(2)) + "%"
                    font: component.font

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: label.anchors.leftMargin
                }
            }
        }
    }

    function indexOfItem(label) {
        for(var key in internal.data) {
            if(internal.data[key]["label"] == label)
                return key
        }
        return -1
    }

    function addUpdateItem(label, value, color) {
        var key = component.indexOfItem(label)

        if(value < component.valueLimit && key == -1)
            return
        if(key == -1) {
            internal.data.push({"label": label,
                               "value": value,
                               "color": color})
        }

        else {
            if(value < component.valueLimit)
                internal.data.splice(key, 1)
            else
                internal.data[key]["value"] = value
        }
        internal.data.sort(internal.compareItems)
        internal.model = Math.min(component.valuesCount, internal.data.length)
        internal.dataChanged()
    }
}
