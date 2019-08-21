#ifndef QUERY_MAKER_H
#define QUERY_MAKER_H

#include "src/state_of_parameters.h"
#include <QString>


class QueryMaker
{
public:
    static QueryMaker &instance();

    QueryMaker(const QueryMaker &) = delete;
    QueryMaker &operator=(QueryMaker &) = delete;

    QString selectDatabaseTableNames() const;
    QString selectPopulationAndTax(const StateOfParameters &state) const;
    QString selectCitiesAndTax(const StateOfParameters &state) const;
    QString selectCities(const StateOfParameters &state) const;
    QString selectStops(const StateOfParameters &state) const;
    QString selectPorts(const StateOfParameters &state) const;
    QString selectTrainStations(const StateOfParameters &state) const;
    QString selectFinancing(const StateOfParameters &state) const;
    QString selectAirports(const StateOfParameters &state) const;
    QString selectHeliports(const StateOfParameters &state) const;

private:
    QueryMaker();

    QString selectAiroprtsAndHeliports(const StateOfParameters &state) const;
};

#endif // QUERY_MAKER_H
