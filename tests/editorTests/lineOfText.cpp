#include <gtest/gtest.h>
#include "lineOfText.Hpp"


// TEST(Line, insertElement) {
//     CodeLineOfText line;
//     CRDTElement crdtElement;
//     Element elementToPlace;
//     elementToPlace.line = 1;
//     elementToPlace.position = "1,3,6";
//     elementToPlace.text = "B";
//     line.insertElement(elementToPlace);
    
//     elementToPlace.line = 1;
//     elementToPlace.position = "1,3";
//     elementToPlace.text = "A";
//     line.insertElement(elementToPlace);

//     EXPECT_STRING_EQ(line.getLine(),"AB");
// }

// TEST(Line, deleteElement) {
//     CodeLineOfText line;
//     CRDTElement crdtElement;
//     Element elementToPlace;
//     elementToPlace.line = 1;
//     elementToPlace.position = "1,3,6";
//     elementToPlace.text = "B";
//     line.insertElement(elementToPlace);
    
//     line.deleteElement(elementToPlace);

//     EXPECT_STRING_EQ(line.getLine(),"");
// }

// TEST(Line, placeOnCount) {
//     CodeLineOfText line;
//     line.placeElementOnCount("B,1", 1);
//     line.placeElementOnCount("A,0", 0);

//     EXPECT_STRING_EQ(line.getLine(),"AB");
// }