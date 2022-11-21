#include <gtest/gtest.h>
#include "lineElement.cpp"


TEST(Text, getText) {
    CodeLineOfText line;
    line.placeElementOnCount("B,1", 1);
    line.placeElementOnCount("A,0", 0);
    line.placeElementOnCount("B,1", 2);

    EXPECT_STRING_EQ(line.getText(),"ABB");

    EXPECT_STRING_EQ(crdtElement.getLine(0),"A");
}
