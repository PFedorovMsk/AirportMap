#include "state_of_parameters.h"


StateOfParameters::StateOfParameters()
    : airports(true)
    , heliports(true)
    , cities(false)
    , financing(false)
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
    , extraBudget(true)
    , onlyFor(false)
    , airportsColor(QColor(128, 128, 255, 128))
    , heliportsColor(QColor(255, 128, 128, 128))
    , citiesColor(QColor(64, 255, 128, 128))
    , financingColor(QColor(192, 192, 64, 128))
{
}
