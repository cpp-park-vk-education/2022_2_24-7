#pragma once
#include "IWorkWithData.hpp"
#include "TextEditor.hpp"
#include "TranslatorFromList.hpp"
#include "WorkWithFile.hpp"
#include "WorkWithLogFile.hpp"

class WorkWithData : public IWorkWithData {
   public:
    WorkWithData();

    std::string operationWithData(
        std::string operation, bool isCommand = false) override;  // If do on server then isCommand set True
    void userFirst(size_t UserId = 0, size_t userCount = 0) override;

    std::string getLine(size_t numberOfLine) override;

    void addFile(std::string path) override;
    std::string getLogFileDirectory() override;
    std::string getFileWithDataDricetory() override;

    ~WorkWithData() override;

   private:
    ITranslator* translator;
    IWorkWithFile* workWithCPP;
    IWorkWithFile* workWithLog;

    IWorkWithText* textEditor;
};
