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
        name: "esri"
        // name: "osm" // name: "mapboxgl"
        // PluginParameter {
        //     name: "osm.mapping.host";
        //     value: "http://a.tile.openstreetmap.org/"
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        visibleRegion: viewOfRussia
    }

    function addCircle(latitude, longitude, color, borderColor, radius) {
        var circle = Qt.createQmlObject('import QtQuick 2.9; Rectangle{ }', map)
        if (circle === null) {
            console.log("Error creating object" + circle.errorString())
            return false
        }
        circle.color = color
        circle.width = radius * 2
        circle.height = radius * 2
        circle.radius = radius
        circle.border.widht = 1
        circle.border.height = 1
        circle.border.color = borderColor
        circle.smooth = true

        var item = Qt.createQmlObject('import QtQuick 2.9; import QtLocation 5.9; MapQuickItem{}', map, "dynamic")
        if (item === null) {
            console.log("Error creating object" + item.errorString())
            return false
        }
        item.sourceItem = circle
        item.anchorPoint.x = Qt.point(radius, radius)
        item.coordinate = QtPositioning.coordinate(latitude, longitude);

        map.addMapItem(item);
        return true
    }
}
