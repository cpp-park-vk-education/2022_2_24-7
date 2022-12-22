#pragma once

#include "Dto.hpp"
#include "IHandler.hpp"
#include "Router.hpp"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>

class Handler : public IHandler { 
   public:
    void handle(std::string ) override;
    void handle(const Dto& ) override;
    std::string reply() override;

   private:
    std::string reply_;
    Dto dto;
    Router router;

    void inputAnalyze(std::string );
    void inputAnalyze(const Dto&);
    void logic();

    void convertMsgToDto(std::string);
    void convertDtoToMsg(const Dto&);
};
