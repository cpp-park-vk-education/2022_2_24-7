#ifndef LineOfText
#define LineOfText = 1

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
    virtual bool insertElement(const Element& el) override;
    virtual bool deleteElement(const Element& el) override;
    
    virtual std::string getLine() override;
    virtual std::string getFormat() override;

    virtual std::string placeElementOnCount(std::string, size_t cnt) override;

    private:
    bool clearAllDoomed();
    bool deleteElement();
    bool createElement();

    std::vector<IElementOfLine*> elementsOfLine;
};
#endif