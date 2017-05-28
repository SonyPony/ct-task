import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "qml/visualization" as Visualization

ApplicationWindow {
    visible: true
    width: 1600
    height: 900
    title: qsTr("View")

    Connections {
        target: ControlAdapter
        onUpdateDataRequest: updateData()
        onShowGraph: {
            if(type == 1)
                viewSwitch.state = "participation"
            else if(type == 2)
                viewSwitch.state = "parties"
            else if(type == 3)
                viewSwitch.state = "detailedParty"
            else
                viewSwitch.state = "none"
        }
    }

    Item {
        id: viewSwitch
        state: "none"

        states: [
            State {
                name: "none"
                PropertyChanges { target: participationView; opacity: 0 }
                PropertyChanges { target: partiesView; opacity: 0 }
                PropertyChanges { target: detailedPartyView; opacity: 0 }
            },
            State {
                name: "participation"
                PropertyChanges { target: participationView; opacity: 1 }
                PropertyChanges { target: partiesView; opacity: 0 }
                PropertyChanges { target: detailedPartyView; opacity: 0 }
            },
            State {
                name: "parties"
                PropertyChanges { target: participationView; opacity: 0 }
                PropertyChanges { target: partiesView; opacity: 1 }
                PropertyChanges { target: detailedPartyView; opacity: 0 }
            },
            State {
                name: "detailedParty"
                PropertyChanges { target: participationView; opacity: 0 }
                PropertyChanges { target: partiesView; opacity: 0 }
                PropertyChanges { target: detailedPartyView; opacity: 1 }
            }
        ]
    }

    Component.onCompleted: updateData()

    FontLoader {
        id: robotoFont
        source: "qrc:/assets/fonts/Roboto-Light.ttf"
    }

    Image {
        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/images/background.jpg"
        anchors.fill: parent
    }

    Visualization.SingleValueView {
        id: participationView

        height: 40

        font: robotoFont.name

        label.text: qsTr("ÚČAST VOLIČŮ")
        label.color: "white"
        label.backgroundColor: "black"

        unit: "%"
        value.color: "white"
        value.backgroundColor: "red"

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    Visualization.PercentageNSortedValueView {
        id: partiesView

        height: 300
        width: 630

        valuesCount: 6
        valueLimit: 5
        textColor: "white"
        labelBackgroundColor: "black"
        font: robotoFont.name

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    Visualization.HistorySingleValueView {
        id: detailedPartyView

        property string selectedParty: ""

        height: 110
        barWidth: 280

        valueUnit: "% " + qsTr("aktuální zisk")
        value.color: "white"
        value.backgroundColor: "black"

        historyUnit: "% " + qsTr("minulý zisk")
        history.color: "white"
        history.backgroundColor: "#7A7A7A"

        labelBackgroundColor: "#F79321"
        font: robotoFont.name

        label: Image {

            source: (detailedPartyView.selectedParty != "")
            ?"qrc:/assets/logos/"+ detailedPartyView.selectedParty + ".svg"
            :""

            fillMode: Image.PreserveAspectFit
            antialiasing: true

            sourceSize.width: 1024
            sourceSize.height: 1014
        }

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    function updateData() {
        participationView.valueReal = Data.participation()

        // update parties view
        var partiesData = Data.partiesData()
        for(var key in partiesData) {
            var partyData = partiesData[key]
            partiesView.addUpdateItem(partyData["name"], partyData["gain"], partyData["color"])
        }

        // update detailed party data
        var selectedParty = Data.selectedDetailedParty()
        var selectedPartyData = Data.partyData(selectedParty)

        detailedPartyView.valueReal = selectedPartyData["gain"]
        detailedPartyView.historyReal = selectedPartyData["lastGain"]
        detailedPartyView.labelBackgroundColor = selectedPartyData["color"]
        detailedPartyView.selectedParty = selectedParty
    }
}
