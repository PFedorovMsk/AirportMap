import QtQuick 2.9
import QtQuick.Window 2.9
import QtLocation 5.9
import QtPositioning 5.9


Rectangle {
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "esri" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 2
    }
}

