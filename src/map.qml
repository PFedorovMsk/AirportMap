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
            value: "file:///D:/Tiles/"
        }
//        PluginParameter {
//            name: "osm.mapping.cache.directory"
//            value: "file:///D:/Tiles/"
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
        id: mapOverlay1
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
                    }
                    onEntered: mapOverlayText.showLabel(textCityName.text, mapOverlay1.fromCoordinate(mqiCities.coordinate))
                    onExited:  mapOverlayText.hideLabel()
                }
            }
        }
    }

    Map {
        id: mapOverlay2
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
                    Text {
                        id: textFinancingName
                        visible: false
                        text: model.name_ru + " - финансирование:\n -бюджетное: " + model.budget_mil_rub +
                              " млн.руб\n -внебюджетное: " +  model.extrabudget_mil_rub + " млн.руб"
                    }
                    onEntered: mapOverlayText.showLabel(textFinancingName.text, mapOverlay2.fromCoordinate(mqiFinancing.coordinate))
                    onExited:  mapOverlayText.hideLabel()
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
                    onEntered: mapOverlayText.showLabel(textAirportName.text, mapOverlay2.fromCoordinate(mqiAirports.coordinate))
                    onExited:  mapOverlayText.hideLabel()
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
                    onEntered: mapOverlayText.showLabel(textHeliportName.text, mapOverlay2.fromCoordinate(mqiHelipoirts.coordinate))
                    onExited:  mapOverlayText.hideLabel()
                }
            }
        }
    }

    Map {
        id: mapOverlayText
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

}
