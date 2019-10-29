#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"
#include "DSLinkedList.h"
#include "DSNode.h"

using namespace std;

TEST_CASE("DSLinkedList class", "[DSLinkedList]"){
    DSLinkedList<int> emptyList;
    DSLinkedList<int> oneElement(8);
    DSLinkedList<int> ascendingList;
    DSLinkedList<DSString> listofStrings;
    DSLinkedList<DSString> oneList("my string");

    for(int i = 0; i < 10; i++){
        ascendingList.insertEnd(i);
    }

    DSString testString[11];
    testString[0] = DSString("dsstring");
    testString[1] = DSString("string w spaces");
    testString[2] = DSString("");
    testString[3] = DSString("UPPERCASE STRING");
    testString[4] = DSString("lower string");
    testString[5] = DSString("\n");
    testString[6] = DSString("");
    testString[7] = DSString("   tab1    tab2    tab3    ");
    testString[8] = DSString("                           ");
    testString[9] = DSString("testDSString");
    testString[10] = DSString("12345678 98765432");
    for (int i = 0; i < 11; i++) {
        listofStrings.insertEnd(testString[i]);
    }

    SECTION("getSize() check"){
        REQUIRE(emptyList.getSize() == 0);
        REQUIRE(oneElement.getSize() == 1);
        REQUIRE(ascendingList.getSize() == 10);
        REQUIRE(listofStrings.getSize() == 11);
        REQUIRE(oneList.getSize() == 1);
    }
    SECTION("[] Operator") {
           REQUIRE(ascendingList[2] == 2);
           REQUIRE(ascendingList[8] == oneElement[0]);
           REQUIRE(listofStrings[3] == "UPPERCASE STRING");
           DSString str = "my string";
           REQUIRE(oneList[0] == str);
       }


}


// SECTION("Copy constructor") {
//REQUIRE(equalStringsList.getSize() == 11);
//REQUIRE(equalStringsList[4] == "lower string");
//            LinkedList<int> integers1 = list2;
//            for (int i = 0; i < 10; i++) {
//                REQUIRE(list2[i] == i);
//            }
//            LinkedList<String> strings1 = list4;
//            REQUIRE(strings1.size() == 0);
//            LinkedList<String> strings2 = list6;
//            REQUIRE(strings2.size() == 1);
//            REQUIRE(strings4[0] = s[10])

