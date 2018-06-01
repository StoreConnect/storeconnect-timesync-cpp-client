//
// Created by Michal Gasztold on 01/06/2018.
//

#ifndef HTTP_GET_INTERFACE_H
#define HTTP_GET_INTERFACE_H

#define ERROR "ERROR"

#include <string>

class http_get_interface {

public:
    http_get_interface();
    virtual std::string get(const std::string &url)=0;
};

#endif //HTTP_GET_INTERFACE_H
