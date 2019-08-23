#include "state_of_parameters.h"


StateOfParameters::StateOfParameters()
    : airports(true)
    , heliports(true)
    , cities(false)
    , financing(false)
    , stops(false)
    , ports(false)
    , trainStations(false)
    , international(true)
    , domestic(true)
    , runwayCoverHard(true)
    , runwayCoverGround(true)
    , runwayType1(true)
    , runwayType2(true)
    , runwayType3(true)
    , runwayType4(true)
    , runwayType5(true)
    , runwayType6(true)
    , runwayNo(true)
    , budget(true)
    , airportsColor(QColor(255, 0, 0, 64))
    , heliportsColor(QColor(32, 159, 223, 64))
    , citiesColor1(QColor(32, 128, 64, 64))
    , citiesColor2(QColor(32, 128, 64, 64))
    , financingColor(QColor(255, 159, 128, 64))
    , stopsColor(QColor(112, 112, 96, 64))
    , portsColor(QColor(0, 0,255, 64))
    , trainStationsColor(QColor(255, 255, 0, 64))
    , year (2017)
    , radius (10)
{
}
