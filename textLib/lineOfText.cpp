#ifndef LineOfText
#define LineOfText

#include "lineElement.cpp"
#include <vector>

class ILineOfText {
    public:
    virtual bool insertElement(const Element& el) = 0;
    virtual bool deleteElement(const Element& el) = 0;
    
    virtual std::string getLine() = 0;
    virtual std::string getFormat() = 0;

    virtual std::string placeElementOnCount(std::string, size_t cnt) = 0;
};

class CodeLineOfText : public ILineOfText {
    public:
    virtual bool insertElement(const Element& el) override {auto tmp = el; return 1; tmp.line++;};
    virtual bool deleteElement(const Element& el) override {auto tmp = el; return 1; tmp.line++;};
    
    virtual std::string getLine() override {return "tes";};
    virtual std::string getFormat() override {return "tes";};

    virtual std::string placeElementOnCount(std::string, size_t cnt) override {return "TES"; cnt++;};

    virtual ~CodeLineOfText() = default;
    private:
    bool clearAllDoomed();
    bool deleteElement();
    bool createElement();

    std::vector<IElementOfLine*> elementsOfLine;
};

#endif