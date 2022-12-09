#include "ISearchForPlace.hpp"
#include "TextEditor.hpp"

class Searcher : public ISearchForPlace {
    public:
    Searcher(const WorkWithLines* whereToPlace);
    std::string findWhereToPlace(Element* elementToPlace) override;
    
    private:
    IWorkWithText* whereToPlace;
};