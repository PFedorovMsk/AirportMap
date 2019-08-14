import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtPositioning 5.12


Rectangle {
    width: 1200
    height: 800
    visible: true

    property variant topLeftRussia:     QtPositioning.coordinate(78.0, 19.0)
    property variant bottomRightRussia: QtPositioning.coordinate(41.0, -169.0)
    property variant viewOfRussia:      QtPositioning.rectangle(topLeftRussia, bottomRightRussia)

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.host"
            value: "http://a.tile.openstreetmap.org/"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        visibleRegion: viewOfRussia
        maximumZoomLevel: 12

        MapItemView {
            id: airportsView
            model: airport_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rectA.width/2
                anchorPoint.y: rectA.height

                sourceItem: Rectangle {
                    id: rectA
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
                        id: tmpTextA
                        visible: false
                        text: model.name_ru
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        tmpTextA.visible = true
                    }
                    onExited: {
                        tmpTextA.visible = false
                    }
                }
            }
        }

        MapItemView {
            id: heliportsView
            model: heliport_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rectH.width/2
                anchorPoint.y: rectH.height

                sourceItem: Rectangle {
                    id: rectH
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
                        id: tmpTextH
                        visible: false
                        text: model.name_ru
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        tmpTextH.visible = true
                    }
                    onExited: {
                        tmpTextH.visible = false
                    }
                }
            }
        }

        MapItemView {
            id: citiesView
            model: cities_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude_city, model.longitude_city)
                anchorPoint.x: rectC.width/2
                anchorPoint.y: rectC.height

                sourceItem: Rectangle {
                    id: rectC
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
                        id: tmpTextC
                        visible: false
                        text: model.name_city
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        tmpTextC.visible = true
                    }
                    onExited: {
                        tmpTextC.visible = false
                    }
                }
            }
        }
    }
}
