#include <iostream>
#include "Router.hpp"

Router::Router() {
    project = Project();
    addHandler("i", InsertSymbol);
    addHandler("d", DeleteSymbol);
};
