#ifndef Lineaa
#define Lineaa
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
    CRDTElement() {childs[0] = new CRDTElement;};
    virtual bool isVisible() override{return 1;};
    virtual bool isDoomed() override {return 1;};
    
    virtual bool placeElement(const Element& elementToPlace) override {if (value > 0) return 2;auto x = elementToPlace; return 0;};
    virtual bool deleteElement(const Element& elementToDelete) override {return 1;auto x = elementToDelete;return 0;};

    virtual std::string getText() override {if (numberOfChilds == 0) return "YES"; return "No";};
    virtual std::string getFormat() override {return "YES";};

    virtual std::string placeElementOnCount(std::string, size_t cnt) override  {return "TES"; cnt++;};



    virtual IElementOfLine& operator=(const Element& element) override {auto _element = element; IElementOfLine* a = new CRDTElement; return *a; };
    private:

    size_t numberOfChilds;
    char value;
    std::array<CRDTElement*,10> childs;
};
#endif