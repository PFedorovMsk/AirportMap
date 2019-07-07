import QtQuick 2.9
import QtQuick.Window 2.9
import QtLocation 5.9
import QtPositioning 5.9


Rectangle {
    width: 512
    height: 512
    visible: true

    property variant topLeftRussia:     QtPositioning.coordinate(78.0, 19.0)
    property variant bottomRightRussia: QtPositioning.coordinate(41.0, -169.0)
    property variant viewOfRussia:      QtPositioning.rectangle(topLeftRussia, bottomRightRussia)

    Plugin {
        id: mapPlugin
        name: "mapboxgl"   // "mapboxgl", "esri", ...
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        visibleRegion: viewOfRussia
    }
}

