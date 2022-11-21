#ifndef Lineaa
#define Lineaa = 1
#include <array>
#include <string>

struct Element {
    size_t line;
    std::string position;
    std::string text;
};

class IElementOfLine
{
    public:
    virtual bool isVisible() = 0;
    virtual bool isDoomed() = 0;
    
    virtual bool placeElement(const Element& elementToPlace) = 0;
    virtual bool deleteElement(const Element& elementToDelete) = 0;
    
    virtual std::string getText() = 0;
    virtual std::string getFormat() = 0;

    virtual std::string placeElementOnCount(std::string, size_t cnt) = 0;

    virtual IElementOfLine& operator=(const Element& element) = 0;
};

class CRDTElement : public IElementOfLine
{
    public:
    CRDTElement() {};
    virtual bool isVisible() override;
    virtual bool isDoomed() override;
    
    virtual bool placeElement(const Element& elementToPlace) override;
    virtual bool deleteElement(const Element& elementToDelete) override;

    virtual std::string getText() override;
    virtual std::string getFormat() override;

    virtual std::string placeElementOnCount(std::string, size_t cnt) override;


    virtual CRDTElement& operator=(const Element& element) override;

    private:

    size_t numberOfChilds;
    char value;
    std::array<CRDTElement*,10> childs;
};
#endif