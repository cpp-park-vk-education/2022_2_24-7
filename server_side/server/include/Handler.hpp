#pragma once

#include "IHandler.hpp"

class Handler : public IHandler {
   public:
    void handleFromClient(std::string msg) override;
    void handleFromBack(std::string msg) override;
    nlohmann::json reply() override;

   private:
    nlohmann::json dto;

    void convertDtoToMsg(std::string msg);
    void convertMsgToDto(std::string msg);
};
