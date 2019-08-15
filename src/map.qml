import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
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

        // Рисуем города:

        MapItemView {
            id: citiesView
            model: cities_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude_city, model.longitude_city)
                anchorPoint.x: rectCity.width / 2
                anchorPoint.y: rectCity.height / 2

                sourceItem: Rectangle {
                    id: rectCity
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    Text {
                        id: textCityName
                        visible: false
                        text: model.name_city
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        textCityName.visible = true
                    }
                    onExited: {
                        textCityName.visible = false
                    }
                }
            }
        }

        // Рисуем финансирование аэропортов/вертодромов:

        MapItemView {
            id: financingView
            model: financing_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rectFinance.width / 2
                anchorPoint.y: rectFinance.height / 2

                sourceItem: Rectangle {
                    id: rectFinance
                    color: model.color
                    radius: (model.model.radius - 10) * (model.summa / 25000) + 10
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    Label {
                        id: textSum
                        visible: false
                        text: model.name_ru + " - финансирование:\n -бюджетное: " + model.budget_mil_rub +
                              " млн.руб\n -внебюджетное: " + model.extrabudget_mil_rub + " млн.руб";
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                        background: Rectangle {
                            color: "white"
                        }
                    }
                    onEntered: {
                        textSum.visible = true
                    }
                    onExited: {
                        textSum.visible = false
                    }
                }
            }
        }

        // Рисуем аэропорты:

        MapItemView {
            id: airportsView
            model: airport_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rectAirport.width / 2
                anchorPoint.y: rectAirport.height / 2

                sourceItem: Rectangle {
                    id: rectAirport
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    Text {
                        id: textAirportName
                        visible: false
                        text: model.name_ru
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        textAirportName.visible = true
                    }
                    onExited: {
                        textAirportName.visible = false
                    }
                }
            }
        }

        // Рисуем вертодромы:

        MapItemView {
            id: heliportsView
            model: heliport_model

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rectHeliport.width / 2
                anchorPoint.y: rectHeliport.height / 2

                sourceItem: Rectangle {
                    id: rectHeliport
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    Text {
                        id: textHeliportName
                        visible: false
                        text: model.name_ru
                        anchors.bottom: parent.top
                        color: "black"
                        font.pointSize: 11
                        antialiasing: true
                    }
                    onEntered: {
                        textHeliportName.visible = true
                    }
                    onExited: {
                        textHeliportName.visible = false
                    }
                }
            }
        }

    }
}
