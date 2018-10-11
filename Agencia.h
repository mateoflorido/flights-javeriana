#ifndef FLIGHTS_JAVERIANA_AGENCIA_H
#define FLIGHTS_JAVERIANA_AGENCIA_H

#include <string>
#include <vector>
#include "Venta.h"

namespace FJA {
    class Agencia {
    public:
        Agencia();

        Agencia(const std::string &m_AgencyID, const std::string &m_Password);

        virtual ~Agencia();

        const std::string &GetAgencyID() const;

        const std::string &GetPassword() const;

        const std::vector<Venta> &GetSales() const;

        void SetAgencyID(const std::string &m_AgencyID);

        void SetPassword(const std::string &m_Password);

        void SetSales(const std::vector<Venta> &m_Sales);

        /**
         * @brief Este método crea una venta en la agencia
         * @param m_Agency Representa el nombre de la agencia
         * @param m_ID Representa el ID de la nueva venta
         * @param m_Flight Representa la ruta de la nueva venta
         * @param m_CustomerID Representa el numero de documento del cliente que realizo la compra
         * @param m_Customer Representa el nombre del cliente que realizó la compra
         * @param m_FlightDate Representa la fecha de el vuelo
         * @param m_BuyDate Representa la fecha de la nueva compra
         * @param m_BuyHour Representa la hora de la nueva compra
         */
        void NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
                     const std::string &m_CustomerID,
                     const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
                     const std::string &m_BuyHour);

        /**
         * @brief Este método hace el reporte de las ventas de la agencia
         * @return Una cadena de caracteres con el reporte de las ventas de la agencia
         */
        std::string SalesReport();

        /**
         * @brief Este método elimina todas las transacciones de la agencia con una fecha anterior a la especificada
         * @param currentDate Representa la fecha especificada para hacer la eleminación de las transacciones anteriores
         */
        void Consolidate(std::string currentDate);

    protected:
        std::string m_AgencyID;
        std::string m_Password;
        std::vector<Venta> m_Sales;

    };
}

#endif //FLIGHTS_JAVERIANA_AGENCIA_H