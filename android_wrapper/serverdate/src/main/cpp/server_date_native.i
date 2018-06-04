%module(directors="1") server_date_native_Wrapper

%include std_string.i
%inline %{
using namespace std;
%}

/* Anything in the following section is added verbatim to the .cxx wrapper file */
%{
#include "http_get_interface.h"
#include "server_date.h"
%}

%feature("director") http_get_interface;

/* This is the list of headers to be wrapped */
/* For Java, it seems we need the file of interest and all files up the inheritance tree */
%include "http_get_interface.h"
%include "server_date.h"