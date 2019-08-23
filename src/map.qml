import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtLocation 5.12
import QtPositioning 5.12


Rectangle {
    id: mainItem
    width: 1200
    height: 800
    visible: true

    property variant topLeftRussia:     QtPositioning.coordinate(78.0, 19.0)
    property variant bottomRightRussia: QtPositioning.coordinate(41.0, -169.0)
    property variant viewOfRussia:      QtPositioning.rectangle(topLeftRussia, bottomRightRussia)

    Plugin {
        id: mapBasePlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "file:///C:/Tiles/"
        }
//        PluginParameter {
//            name: "osm.mapping.cache.directory"
//            value: "file:///C:/Tiles/"
//        }
    }

    Map {
        id: mapBase
        gesture.enabled: true
        anchors.fill: parent
        visibleRegion: viewOfRussia
        maximumZoomLevel: 10
        z: parent.z + 1
        plugin: mapBasePlugin

        Component.onCompleted: {
            for( var i_type in supportedMapTypes ) {
                if( supportedMapTypes[i_type].name.localeCompare( "Custom URL Map" ) === 0 ) {
                    activeMapType = supportedMapTypes[i_type]
                }
            }
        }
    }

    Map {
        id: mapOverlayCities
        anchors.fill: parent
        plugin: Plugin { name: "itemsoverlay" }
        gesture.enabled: false
        center: mapBase.center
        color: 'transparent'
        minimumFieldOfView: mapBase.minimumFieldOfView
        maximumFieldOfView: mapBase.maximumFieldOfView
        minimumTilt: mapBase.minimumTilt
        maximumTilt: mapBase.maximumTilt
        minimumZoomLevel: mapBase.minimumZoomLevel
        maximumZoomLevel: mapBase.maximumZoomLevel
        zoomLevel: mapBase.zoomLevel
        tilt: mapBase.tilt;
        bearing: mapBase.bearing
        fieldOfView: mapBase.fieldOfView
        z: mapBase.z + 1
        layer.enabled: true

        // Рисуем города:

        MapItemView {
            id: citiesView
            model: cities_model

            delegate: MapQuickItem {
                id: mqiCities
                coordinate: QtPositioning.coordinate(model.latitude_city, model.longitude_city)
                anchorPoint.x: rectCity.width / 2
                anchorPoint.y: rectCity.height / 2

                sourceItem: Rectangle {
                    id: rectCity
                    color: normaledColor(model.color, model.additionalColor, model.minParamValue, model.maxParamValue, model.value)
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
                    }
                    onEntered: mapOverlayLabels.showLabel(textCityName.text, mapOverlayCities.fromCoordinate(mqiCities.coordinate))
                    onExited:  mapOverlayLabels.hideLabel()
                }
            }
        }

        MapItemView {
            id: stopsView
            model: stops_model

            delegate: MapQuickItem {
                id: mqiStops
                coordinate: QtPositioning.coordinate(model.latitude_bus, model.longitude_bus)
                anchorPoint.x: rectStop.width / 2
                anchorPoint.y: rectStop.height / 2

                sourceItem: Rectangle {
                    id: rectStop
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }
            }
        }

        MapItemView {
            id: portsView
            model: ports_model

            delegate: MapQuickItem {
                id: mqiPorts
                coordinate: QtPositioning.coordinate(model.latitude_boat, model.longitude_boat)
                anchorPoint.x: rectPort.width / 2
                anchorPoint.y: rectPort.height / 2

                sourceItem: Rectangle {
                    id: rectPort
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }
            }
        }

        MapItemView {
            id: trainStationsView
            model: train_stations_model

            delegate: MapQuickItem {
                id: mqiTrainStations
                coordinate: QtPositioning.coordinate(model.latitude_rail, model.longitude_rail)
                anchorPoint.x: rectTrainStation.width / 2
                anchorPoint.y: rectTrainStation.height / 2

                sourceItem: Rectangle {
                    id: rectTrainStation
                    color: model.color
                    radius: model.radius
                    width: radius * 2
                    height: radius * 2
                    border.width: 1
                    border.color: model.borderColor
                    smooth: false
                }
            }
        }
    }

    Map {
        id: mapOverlayMainObjects
        anchors.fill: parent
        plugin: Plugin { name: "itemsoverlay" }
        gesture.enabled: false
        center: mapBase.center
        color: 'transparent'
        minimumFieldOfView: mapBase.minimumFieldOfView
        maximumFieldOfView: mapBase.maximumFieldOfView
        minimumTilt: mapBase.minimumTilt
        maximumTilt: mapBase.maximumTilt
        minimumZoomLevel: mapBase.minimumZoomLevel
        maximumZoomLevel: mapBase.maximumZoomLevel
        zoomLevel: mapBase.zoomLevel
        tilt: mapBase.tilt;
        bearing: mapBase.bearing
        fieldOfView: mapBase.fieldOfView
        z: mapBase.z + 2
        layer.enabled: true

        // Рисуем финансирование аэропортов/вертодромов:

        MapItemView {
            id: financingView
            model: financing_model

            delegate: MapQuickItem {
                id: mqiFinancing
                coordinate: QtPositioning.coordinate(model.air_latitude, model.air_longitude)
                anchorPoint.x: rectFinance.width / 2
                anchorPoint.y: rectFinance.height / 2

                sourceItem: Rectangle {
                    id: rectFinance
                    color: model.color
                    radius: (model.model.radius - 10) * (model.summa / model.maxParamValue) + 10
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
                        id: textFinancingName
                        visible: false
                        text: model.name_ru + " - финансирование:\n -бюджетное: " + model.budget_mil_rub +
                              " млн.руб\n -внебюджетное: " +  model.extrabudget_mil_rub + " млн.руб"
                    }
                    onEntered: mapOverlayLabels.showLabel(textFinancingName.text, mapOverlayMainObjects.fromCoordinate(mqiFinancing.coordinate))
                    onExited:  mapOverlayLabels.hideLabel()
                }
            }
        }

        // Рисуем аэропорты:

        MapItemView {
            id: airportsView
            model: airport_model

            delegate: MapQuickItem {
                id: mqiAirports
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
                    }
                    onEntered: mapOverlayLabels.showLabel(textAirportName.text, mapOverlayMainObjects.fromCoordinate(mqiAirports.coordinate))
                    onExited:  mapOverlayLabels.hideLabel()
                }
            }
        }

        // Рисуем вертодромы:

        MapItemView {
            id: heliportsView
            model: heliport_model

            delegate: MapQuickItem {
                id: mqiHelipoirts
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
                    }
                    onEntered: mapOverlayLabels.showLabel(textHeliportName.text, mapOverlayMainObjects.fromCoordinate(mqiHelipoirts.coordinate))
                    onExited:  mapOverlayLabels.hideLabel()
                }
            }
        }
    }

    Map {
        id: mapOverlayLabels
        anchors.fill: parent
        plugin: Plugin { name: "itemsoverlay" }
        gesture.enabled: false
        center: mapBase.center
        color: 'transparent'
        minimumFieldOfView: mapBase.minimumFieldOfView
        maximumFieldOfView: mapBase.maximumFieldOfView
        minimumTilt: mapBase.minimumTilt
        maximumTilt: mapBase.maximumTilt
        minimumZoomLevel: mapBase.minimumZoomLevel
        maximumZoomLevel: mapBase.maximumZoomLevel
        zoomLevel: mapBase.zoomLevel
        tilt: mapBase.tilt;
        bearing: mapBase.bearing
        fieldOfView: mapBase.fieldOfView
        z: mapBase.z + 3
        layer.enabled: true

        Label {
            id: textSum
            visible: false
            color: "black"
            font.pointSize: 11
            antialiasing: true
            background: Rectangle {
                color: "white"
            }
        }

        function showLabel(text, point)
        {
            textSum.text = text
            textSum.x = point.x + 25
            textSum.y = point.y - 25
            textSum.visible = true
        }

        function hideLabel()
        {
            textSum.visible = false
        }
    }

    function normaledColor(color1, color2, minVal, maxVal, value)
    {
        if (color1 === color2) {
            return color1
        }

        var n = (value - maxVal) / (maxVal - minVal);

        var r = color1.r * n + color2.r * (1 - n)
        var g = color1.g * n + color2.g * (1 - n)
        var b = color1.b * n + color2.b * (1 - n)
        var a = color1.a * n + color2.a * (1 - n)

        return Qt.rgba(r, g, b, a)
    }
}
