#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"
#include "DSLinkedList.h"
#include "DSNode.h"
#include "DSStack.h"

using namespace std;

TEST_CASE("DSLinkedList class", "[DSLinkedList]"){
    DSLinkedList<int> emptyListInt;
    DSLinkedList<DSString> emptyListString;
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

    DSLinkedList<DSString> equalStringList;
    equalStringList = listofStrings;

    SECTION("getSize() check"){
        REQUIRE(emptyListInt.getSize() == 0);
        REQUIRE(oneElement.getSize() == 1);
        REQUIRE(ascendingList.getSize() == 10);
        REQUIRE(listofStrings.getSize() == 11);
        REQUIRE(oneList.getSize() == 1);
    }

    SECTION("[] operator check") {
        REQUIRE(ascendingList[2] == 2);
        REQUIRE(ascendingList[8] == oneElement[0]);
        REQUIRE(listofStrings[3] == "UPPERCASE STRING");
        DSString str = "my string";
        REQUIRE(oneList[0] == str);
    }

    SECTION("copy constructor check") {
        REQUIRE(equalStringList.getSize() == 11);
        REQUIRE(equalStringList[4] == "lower string");
        //DSLinkedList<int> integers1 = ascendingList;
        for (int i = 0; i < 10; i++) {
            REQUIRE(ascendingList[i] == i);
        }
        DSLinkedList<DSString> strings1 = emptyListString;
        REQUIRE(strings1.getSize() == 0);
        //DSLinkedList<DSString> strings2 = oneList;
        //REQUIRE(strings2.getSize() == 1);
        //REQUIRE(strings2[0] == testString[10]);
    }
    SECTION("get function check") {
        REQUIRE(ascendingList.get(2) == 2);
        REQUIRE(ascendingList.get(8) == oneElement.get(0));
        REQUIRE(listofStrings.get(3) == "UPPERCASE STRING");
        DSString str = "my string";
        REQUIRE(oneList.get(0) == str);
    }
    SECTION("assignment operator check") {
        DSLinkedList<DSString> testString;
        testString = emptyListString;
        REQUIRE(testString.getSize() == 0);
        testString = oneList;
        REQUIRE(testString.getSize() == 1);
        //REQUIRE(strings1[0] == testString[10]);
        DSLinkedList<int> integers1(4);
        ascendingList = integers1;
        REQUIRE(ascendingList.getSize() == 1);
        REQUIRE(ascendingList[0] == 4);
    }
    SECTION("add to end check") {
        emptyListInt.insertEnd(3);
        REQUIRE(emptyListInt.getSize() == 1);
        REQUIRE(emptyListInt[0] == 3);
        DSString str = "UPPERCASE STRING";
        listofStrings.insertEnd(str);
        REQUIRE(listofStrings.getSize() == 12);
        REQUIRE(listofStrings[11] == listofStrings[3]);
        oneList.insertEnd("Los Angeles");
        oneList.insertEnd("Los Angeles");
        //oneList.print();
        REQUIRE(oneList[1] == oneList[2]);
    }
    SECTION("add to front check") {
        emptyListInt.insertFront(3);
        REQUIRE(emptyListInt.getSize() == 1);
        REQUIRE(emptyListInt[0] == 3);
        DSString str = "UPPERCASE STRING";
        listofStrings.insertFront(str);
        REQUIRE(listofStrings.getSize() == 12);
        REQUIRE(listofStrings[0] == listofStrings[4]);
        //REQUIRE(listofStrings[11] == "yo");
        DSString str1 = oneList[0];
        oneList.insertFront("");
        oneList.insertFront("");
        REQUIRE(oneList[0] == oneList[1]);
        REQUIRE(oneList[2] == str1);
    }
    SECTION("remove function check") {
        oneElement.remove(0);
        REQUIRE(oneElement.getSize() == 0);
        listofStrings.remove(10);
        listofStrings.remove(9);
        listofStrings.remove(8);
        REQUIRE(listofStrings.getSize() == 8);
        REQUIRE(listofStrings[listofStrings.getSize()-1] == "   tab1    tab2    tab3    ");
        DSString str = "UPPERCASE STRING";
        oneList.insertEnd(str);
        oneList.insertEnd(str);
        oneList.remove(oneList.getSize()-1);
        REQUIRE(oneList.getSize() == 2);
        REQUIRE(oneList[1] == str);
        equalStringList.remove(1);
        equalStringList.remove(1);
        REQUIRE(equalStringList.getSize() == 9);
        REQUIRE(equalStringList[1] == listofStrings[3]);
    }
    SECTION("clear function check") {
        ascendingList.emptyList();
        REQUIRE(ascendingList.getSize() == 0);
        listofStrings.emptyList();
        REQUIRE(listofStrings.getSize() == 0);
    }
    SECTION("insert middle function check"){
        equalStringList.insertMiddle(5,"insert");
        REQUIRE(equalStringList[5] == "insert");
    }
}

TEST_CASE("Stack class", "[stack]"){

    DSStack<int> s1;
    DSStack<DSString> s2;
    DSStack<int> s3;
    DSStack<DSString> s4;

    for (int i = 0; i < 10; i++) {
        s1.push(i);
    }

    DSString s[11];
    s[0] = DSString("test string");
    s[1] = DSString("another test string");
    s[2] = DSString("");
    s[3] = DSString("UPPERCASE STRING");
    s[4] = DSString("lower string");
    s[5] = DSString("\n");
    s[6] = DSString("");
    s[7] = DSString("   tab1    tab2    tab3    ");
    s[8] = DSString("                           "); //7 tabs
    s[9] = DSString("testString");
    s[10] = DSString("hell it me");
    for (int i = 0; i < 11; i++) {
        s2.push(s[i]);
    }

    SECTION("pop function check") {
        REQUIRE(s1.pop() == 9);
        REQUIRE(s1.size() == 9);
        REQUIRE(s2.pop() == "hell it me");
        REQUIRE(s2.pop() == "testString");
        REQUIRE(s2.size() == 9);
    }

    SECTION("peek function check") {
        REQUIRE(s1.peek() == 9);
        REQUIRE(s1.size() == 10);
        REQUIRE(s2.peek() == "hell it me");
        REQUIRE(s2.size() == 11);
    }

    SECTION("push function check") {
        s3.push(5);
        REQUIRE(s3.peek() == 5);
        REQUIRE(s3.isEmpty() == false);
        REQUIRE(s3.pop() == 5);
        REQUIRE(s3.isEmpty() == true);
        s4.push("pls");
        s4.push("work");
        s4.push("oof");
        REQUIRE(s4.size() == 3);
        REQUIRE(s4.isEmpty() == false);
        REQUIRE(s4.peek() == "oof");
    }

    SECTION("isEmpty function check") {
        REQUIRE(s1.isEmpty() == false);
        REQUIRE(s2.isEmpty() == false);
        REQUIRE(s3.isEmpty() == true);
        REQUIRE(s4.isEmpty() == true);
    }
}

