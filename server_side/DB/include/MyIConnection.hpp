#pragma once

#include <boost/shared_ptr.hpp>
#include "../../server/include/IConnection.hpp"

using ConnectionPtr = boost::shared_ptr<IConnection>;
// это интерфейс сущности из сервера проекта, он служит для последующей интеграции
