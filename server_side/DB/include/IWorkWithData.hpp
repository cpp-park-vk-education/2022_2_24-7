#pragma once

#include <string>

class IWorkWithData {
   public:
    virtual std::string operationWithData(std::string, bool) = 0;
    virtual void userFirst(size_t, size_t) = 0;
    virtual std::string getLine(size_t) = 0;
    virtual void addDirectoryToPlaceFiles(
        std::string) = 0;  //                  сюда я передаю путь до срр файла,
    virtual void addFile(std::string) = 0;  // с которым работают клиенты
    virtual std::string getLogFileDirectory() = 0;
    virtual std::string getFileWithDataDirectory() = 0;
};
// это интерфейс сущности из системы проекта, он служит для последующей
// интеграции

class WorkWithData : public IWorkWithData {
   public:
    WorkWithData(){};
    std::string operationWithData(std::string, bool) override { return "a"; };
    void userFirst(size_t, size_t) override{};
    std::string getLine(size_t) override { return "a"; };
    void addDirectoryToPlaceFiles(
        std::string) override{};  //                       сюда я передаю путь до срр файла,
    void addFile(std::string) override{};  // с которым работают клиенты
    std::string getLogFileDirectory() override { return "a"; };
    std::string getFileWithDataDirectory() override { return "a"; };
};
