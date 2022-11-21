#ifndef text41
#define text41

#include <string>
#include "lineOfText.cpp"
#include <iostream>

class ITextEditor {
    public:
    virtual bool insertElement(const Element& el) = 0;
    virtual bool deleteElement(const Element& el) = 0;

    virtual std::string getLine(const size_t& numberOfLine) = 0;
    virtual std::string getText() = 0;
    virtual std::string getFormatLine(const size_t& line) = 0;

    virtual std::string placeElementOnCount(std::string inLine, size_t cnt) = 0;

    virtual bool addDirectory(std::string path) = 0;
};

class CodeTextEditor : public ITextEditor {
    public:
    virtual bool insertElement(const Element& el) override {auto tmp = el.line; tmp++; return true;};
    virtual bool deleteElement(const Element& el) override {auto tmp = el.line; tmp++; return true;};

    virtual std::string getLine(const size_t& numberOfLine) override {auto tmp = numberOfLine; tmp++; return "Yes";};
    virtual std::string getText() override {return "no";};
    virtual std::string getFormatLine(const size_t& line) override {auto tmp = line + 1;return "Yes"; std::cout << tmp;};

    virtual std::string placeElementOnCount(std::string inLine, size_t cnt) override {auto tmp = cnt; tmp++; auto a = inLine; return "No";};

    virtual bool addDirectory(std::string path) override {auto a = path; return 1;};
    
    private:
    std::vector<ILineOfText> lines;
    std::string path;
};
#endif