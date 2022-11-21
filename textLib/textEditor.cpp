#ifndef text41
#define text41 = 1

#include <string>
#include "lineOfText.cpp"

class ITextEditor {
    public:
    virtual bool insertElement(const Element& el) = 0;
    virtual bool deleteElement(const Element& el) = 0;

    virtual std::string getLine(const size_t& numberOfLine) = 0;
    virtual std::string getText() = 0;
    virtual std::string getFormatLine(const size_t& line) = 0;

    virtual std::string placeElementOnCount(std::string, size_t cnt) = 0;

    virtual bool addDirectory(std::string path) = 0;
};

class CodeTextEditor : public ITextEditor {
    public:
    virtual bool insertElement(const Element& el) override;
    virtual bool deleteElement(const Element& el) override;

    virtual std::string getLine(const size_t& numberOfLine) override;
    virtual std::string getText() override;
    virtual std::string getFormatLine(const size_t& line) override;

    virtual std::string placeElementOnCount(std::string, size_t cnt) override;

    virtual bool addDirectory(std::string path) override;
    
    private:
    std::vector<ILineOfText> lines;
    std::string path;
};
#endif