//
// Created by Michal Gasztold on 01/06/2018.
//

#ifndef HTTP_GET_INTERFACE_H
#define HTTP_GET_INTERFACE_H

#define ERROR "ERROR"

class http_get_interface {

public:
    virtual std::string get(std::string &url)=0;
};

#endif //HTTP_GET_INTERFACE_H
