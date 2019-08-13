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
        name: "osm"
        PluginParameter {
//            name: "osm.mapping.host"
//            value: "http://a.tile.openstreetmap.org/"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        visibleRegion: viewOfRussia
        maximumZoomLevel: 11

        MapItemView {
            id: airportsView
            model: airport_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rect.width/2
                anchorPoint.y: rect.height

                sourceItem: Rectangle {
                    id: rect
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: true
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    Text {
                        id: tmpText
                        visible: false
                        text: model.name_ru
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        tmpText.visible = true
                    }
                    onExited: {
                        tmpText.visible = false
                    }
                }
            }
        }
    }
}
