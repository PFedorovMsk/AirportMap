#ifndef STATE_OF_PARAMETERS_H
#define STATE_OF_PARAMETERS_H

#include <QColor>
#include <QString>


struct StateOfParameters {
    bool    showAirports;
    bool    showAirportsInternational;
    bool    showAirportsDomestic;
    bool    showAirportsWithHardCoverOfRunway;
    bool    showAirportsWithGroundCoverOfRunway;
    bool    showAirportsWithRunwayType1;
    bool    showAirportsWithRunwayType2;
    bool    showAirportsWithRunwayType3;
    bool    showAirportsWithRunwayType4;
    bool    showAirportsWithRunwayType5;
    bool    showAirportsWithRunwayType6;
    bool    showAirportsWithRunwayTypeNo;
    bool    showAirportsWithConstantLighting;
    bool    showAirportsWithLightingByRequest;
    bool    showAirportsWithoutLighting;
    bool    showAirportsOnlyForRegion;
    QString airportsRegion;
    QColor  airportsColor;
    bool    showAirportsFinancing;
    QColor  airportsFinancingColor;
    bool    showAirportsTraffic;
    QColor  airportsTrafficColor;

    bool    showHeliports;
    bool    showHeliportsOnlyForRegion;
    QString heliportsRegion;
    QColor  heliportsColor;

    StateOfParameters();
};


#endif // STATE_OF_PARAMETERS_H
