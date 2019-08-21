#ifndef STATE_OF_PARAMETERS_H
#define STATE_OF_PARAMETERS_H

#include <QColor>
#include <QString>


struct StateOfParameters {
    bool airports;
    bool heliports;
    bool cities;
    bool financing;
    bool stops;
    bool ports;
    bool trainStations;
    bool international;
    bool domestic;
    bool runwayCoverHard;
    bool runwayCoverGround;
    bool runwayType1;
    bool runwayType2;
    bool runwayType3;
    bool runwayType4;
    bool runwayType5;
    bool runwayType6;
    bool runwayNo;
    bool budget;

    QColor airportsColor;
    QColor heliportsColor;
    QColor citiesColor1;
    QColor citiesColor2;
    QColor financingColor;
    QColor stopsColor;
    QColor portsColor;
    QColor trainStationsColor;

    int year;
    int radius;

    QStringList regionList;

    StateOfParameters();
};


#endif // STATE_OF_PARAMETERS_H
