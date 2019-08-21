#include "query_maker.h"


QueryMaker::QueryMaker() {}

QueryMaker &QueryMaker::instance()
{
    static QueryMaker queryMakerInstance;
    return queryMakerInstance;
}

QString QueryMaker::selectDatabaseTableNames() const
{
    QString query = "SELECT table_name FROM information_schema.tables WHERE table_schema ";
    query += "NOT IN ('information_schema', 'pg_catalog') AND table_schema IN ('public')";

    return query;
}

QString QueryMaker::selectPopulationAndTax(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT TIM.tax_social_avg::NUMERIC, SUM(TIC.pop_total) AS POPULATION FROM tab_local_cities AS TLC ";
    query += "INNER JOIN tab_municipal_areas AS TMA ON TLC.id_oktmo_municip = TMA.id_oktmo_municip ";
    query += "INNER JOIN tab_areas AS TA ON TMA.id_oktmo_area = TA.id_oktmo_area ";
    query += "INNER JOIN tab_federal_areas AS TFA ON TA.id_fed_area = TFA.id_fed_area ";
    query += "INNER JOIN tab_indic_municipal AS TIM ON TMA.id_oktmo_municip = TIM.id_oktmo_municip ";
    query += "INNER JOIN tab_indic_cities AS TIC ON TLC.id_oktmo_city = TIC.id_oktmo_city WHERE (";

    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TA.name_area ='" + state.regionList.at(i) + "' OR ";
    }

    query += "TIM.year = " + QString::number(state.year) + ")";
    query += "GROUP BY TIM.tax_social_avg ORDER BY TIM.tax_social_avg ASC";

    return query;
}

QString QueryMaker::selectCitiesAndTax(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT TIM.tax_social_avg::NUMERIC, count(TLC.name_city) AS num_city FROM tab_local_cities AS TLC ";
    query += "INNER JOIN tab_municipal_areas AS TMA ON TLC.id_oktmo_municip = TMA.id_oktmo_municip ";
    query += "INNER JOIN tab_areas AS TA ON TMA.id_oktmo_area = TA.id_oktmo_area ";
    query += "INNER JOIN tab_federal_areas AS TFA ON TA.id_fed_area = TFA.id_fed_area ";
    query += "INNER JOIN tab_indic_municipal AS TIM ON TMA.id_oktmo_municip = TIM.id_oktmo_municip ";
    query += "INNER JOIN tab_indic_cities AS TIC ON TLC.id_oktmo_city = TIC.id_oktmo_city WHERE (";

    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TA.name_area ='" + state.regionList.at(i) + "' OR ";
    }

    query += "TIM.year = " + QString::number(state.year) + ")";
    query += "GROUP BY TIM.tax_social_avg ORDER BY TIM.tax_social_avg ASC";

    return query;
}

QString QueryMaker::selectCities(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT TLC.name_city, TLC.latitude_city, TLC.longitude_city ";
    query += "FROM tab_local_cities AS TLC ";
    query += "INNER JOIN tab_municipal_areas AS TMA ON TLC.id_oktmo_municip = TMA.id_oktmo_municip ";
    query += "INNER JOIN tab_areas AS TA ON TMA.id_oktmo_area = TA.id_oktmo_area ";
    query += "INNER JOIN tab_federal_areas AS TFA ON TA.id_fed_area = TFA.id_fed_area WHERE (";

    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TA.name_area = '" + state.regionList.at(i) + "' ";
        if (i < state.regionList.count() - 1) {
            query += "OR ";
        }
    }

    query += ")";

    return query;
}

QString QueryMaker::selectStops(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT t2.name_bus_station, t2.latitude_bus, t2.longitude_bus FROM (SELECT tlc.latitude_city, ";
    query += "tlc.longitude_city FROM tab_local_cities AS tlc ";
    query += "INNER JOIN tab_municipal_areas AS tma ON tlc.id_oktmo_municip = tma.id_oktmo_municip ";
    query += "INNER JOIN tab_areas AS ta ON tma.id_oktmo_area = ta.id_oktmo_area WHERE (";

    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TA.name_area = '" + state.regionList.at(i) + "' ";
        if (i < state.regionList.count() - 1) {
            query += "OR ";
        }
    }

    query += ")) AS t1, tab_bus_stations AS t2 WHERE ";
    query += "(6371 * acos(sind(t2.latitude_bus) * sind(t1.latitude_city) + cosd(t2.latitude_bus) * ";
    query += "cosd(t1.latitude_city) * cosd(t2.longitude_bus - t1.longitude_city)) ) < ";
    query += QString::number(state.radius);
    query += " GROUP BY t2.name_bus_station, t2.latitude_bus, t2.longitude_bus";

    return query;
}

QString QueryMaker::selectPorts(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT t2.name_boat_station, t2.latitude_boat, t2.longitude_boat FROM (";
    query += "SELECT tlc.latitude_city, tlc.longitude_city FROM tab_local_cities AS tlc ";
    query += "INNER JOIN tab_municipal_areas AS tma ON tlc.id_oktmo_municip = tma.id_oktmo_municip ";
    query += "INNER JOIN tab_areas AS ta ON tma.id_oktmo_area = ta.id_oktmo_area WHERE (";

    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TA.name_area = '" + state.regionList.at(i) + "' ";
        if (i < state.regionList.count() - 1) {
            query += "OR ";
        }
    }

    query += ")) AS t1, tab_boat_stations AS t2 WHERE ";
    query += "(6371 * acos(sind(t2.latitude_boat) * sind(t1.latitude_city) + cosd(t2.latitude_boat) * ";
    query += "cosd(t1.latitude_city) * cosd(t2.longitude_boat - t1.longitude_city)) ) < ";
    query += QString::number(state.radius);
    query += " GROUP BY t2.name_boat_station, t2.latitude_boat, t2.longitude_boat";

    return query;
}

QString QueryMaker::selectTrainStations(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT t2.station_name, t2.latitude_rail, t2.longitude_rail FROM (";
    query += "SELECT tlc.latitude_city, tlc.longitude_city FROM tab_local_cities AS tlc ";
    query += "INNER JOIN tab_municipal_areas AS tma ON tlc.id_oktmo_municip = tma.id_oktmo_municip ";
    query += "INNER JOIN tab_areas AS ta ON tma.id_oktmo_area = ta.id_oktmo_area WHERE (";

    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TA.name_area = '" + state.regionList.at(i) + "' ";
        if (i < state.regionList.count() - 1) {
            query += "OR ";
        }
    }

    query += ")) AS t1, tab_rail_stations AS t2 WHERE ";
    query += "(6371 * acos(sind(t2.latitude_rail) * sind(t1.latitude_city) + cosd(t2.latitude_rail) * cosd(";
    query += "t1.latitude_city) * cosd(t2.longitude_rail - t1.longitude_city)) ) < ";
    query += QString::number(state.radius);
    query += " GROUP BY t2.station_name, t2.latitude_rail, t2.longitude_rail";

    return query;
}

QString QueryMaker::selectFinancing(const StateOfParameters &state) const
{
    QString query = "";

    query += "SELECT TA.name_ru, TA.air_latitude, TA.air_longitude, TE.budget_mil_rub::numeric, ";
    query += "TE.extrabudget_mil_rub::numeric, SUM(budget_mil_rub + extrabudget_mil_rub)::numeric AS summa ";
    query += "FROM tab_airports AS TA INNER JOIN tab_economic as TE ON TA.id_air = TE.id_air ";

    if (state.budget) {
        query += "WHERE TE.extrabudget_mil_rub::numeric <= 0 ";
    }

    query += "GROUP BY TA.name_ru, TA.air_latitude, TA.air_longitude, TE.budget_mil_rub, TE.extrabudget_mil_rub ";

    return query;
}

QString QueryMaker::selectAiroprtsAndHeliports(const StateOfParameters &state) const
{
    bool needTabStrips = (!(state.runwayCoverHard && state.runwayCoverGround) ||
                          !(state.runwayType1 && state.runwayType2 && state.runwayType3 && state.runwayType4 &&
                            state.runwayType5 && state.runwayType6 && state.runwayNo));

    QString query = "SELECT TAir.name_ru, TAir.air_latitude, TAir.air_longitude FROM tab_airports AS TAir ";
    if (needTabStrips) {
        query += "INNER JOIN tab_strips AS TStrips ON TAir.id_air = TStrips.id_air ";
    }
    query += "WHERE ";

    if (state.international && !state.domestic) {
        query += " TAir.id_air_class = 1 AND ";
    } else if (!state.international && state.domestic) {
        query += " TAir.id_air_class = 2 AND ";
    }

    if (state.runwayCoverHard && !state.runwayCoverGround) {
        query += " TStrips.id_str_type = 1 AND ";
    } else if (!state.runwayCoverHard && state.runwayCoverGround) {
        query += " TStrips.id_str_type = 2 AND ";
    }

    if (needTabStrips) {
        QString subQuery = "";
        if (state.runwayType1) {
            subQuery += "TStrips.id_str_class = 1";
        }
        if (state.runwayType2) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 2";
        }
        if (state.runwayType3) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 3";
        }
        if (state.runwayType4) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 4";
        }
        if (state.runwayType5) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 5";
        }
        if (state.runwayType6) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 6";
        }
        if (state.runwayNo) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 7";
        }
        query += " (" + subQuery + ") AND ";
    }

    return query;
}

QString QueryMaker::selectAirports(const StateOfParameters &state) const
{
    return selectAiroprtsAndHeliports(state) + "TAir.id_air_type = 1";
}

QString QueryMaker::selectHeliports(const StateOfParameters &state) const
{
    return selectAiroprtsAndHeliports(state) + "TAir.id_air_type = 2";
}
