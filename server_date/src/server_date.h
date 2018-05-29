//
// Created by Adrien Jonquet on 29/05/2018.
//

#ifndef SERVER_DATE_H
#define SERVER_DATE_H


#include <string>
#include <easyhttpcpp/Response.h>
#include "models.h"


class server_date {

private:
    static void dumpResponse(easyhttpcpp::Response::Ptr pResponse);

public:
    static bool get_date(std::string url);

};

#endif //LOCATION_MULTILATERATION_H