#include <gtest/gtest.h>
#include "lineElement.hpp"

TEST(Element, isVisible) {
    CRDTElement crdtElement;
    Element elementToPlace;
    elementToPlace.line = 1;
    elementToPlace.position = "1";
    elementToPlace.text = "A";

    EXPECT_TRUE(crdtElement.isDoomed());
    crdtElement.placeElement(elementToPlace);
    EXPECT_FALSE(crdtElement.isDoomed());
}

TEST(Element, visible) {
    CRDTElement crdtElement;
    Element elementToPlace;
    elementToPlace.line = 1;
    elementToPlace.position = "1,3,6";
    elementToPlace.text = "A";
    crdtElement = elementToPlace;

    EXPECT_TRUE(crdtElement.isVisible());
    crdtElement.deleteElement(elementToPlace);
    EXPECT_FALSE(crdtElement.isVisible());
}

TEST(Element, placeElement) {
    CRDTElement crdtElement;
    Element elementToPlace;
    elementToPlace.line = 1;
    elementToPlace.position = "1,3,6";
    elementToPlace.text = "B";
    crdtElement = elementToPlace;
    
    elementToPlace.line = 1;
    elementToPlace.position = "1,3";
    elementToPlace.text = "A";
    crdtElement.placeElement(elementToPlace);

    EXPECT_STRING_EQ(crdtElement.getText(),"AB");
}

TEST(Element, getFormat) {
    CRDTElement crdtElement;
    Element elementToPlace;
    elementToPlace.line = 1;
    elementToPlace.position = "1,3,6";
    elementToPlace.text = "B";
    crdtElement = elementToPlace;
    
    elementToPlace.line = 1;
    elementToPlace.position = "1,3";
    elementToPlace.text = "A";
    crdtElement.placeElement(elementToPlace);

    EXPECT_STRING_EQ(crdtElement.getFormat(),"A:1,3;B:1,3,6;");
}


TEST(Element, getFormat) {
    CRDTElement crdtElement;
    Element elementToPlace;
    elementToPlace.line = 1;
    elementToPlace.position = "1,3,6";
    elementToPlace.text = "B";
    crdtElement = elementToPlace;
    
    elementToPlace.line = 1;
    elementToPlace.position = "1,3";
    elementToPlace.text = "A";
    crdtElement.placeElement(elementToPlace);
    
    elementToPlace.line = 1;
    elementToPlace.position = "1,3";
    elementToPlace.text = "A";
    crdtElement.placeElement("a",2);

    EXPECT_STRING_EQ(crdtElement.getFormat(),"A:1,3;a:2,3;B:1,3,6;");
}

TEST(Element, getFormat) {
    CRDTElement crdtElement;
    Element elementToPlace;
    elementToPlace.line = 1;
    elementToPlace.position = "1,3,6";
    elementToPlace.text = "B";
    crdtElement = elementToPlace;
    
    elementToPlace.line = 1;
    elementToPlace.position = "1,3";
    elementToPlace.text = "A";
    crdtElement.placeElement(elementToPlace);
    
    elementToPlace.line = 1;
    elementToPlace.position = "1,3";
    elementToPlace.text = "A";
    crdtElement.placeElementOnCount("a",5);

    EXPECT_STRING_EQ(crdtElement.getText(),"ABa");
}
