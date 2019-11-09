#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"
#include "DSLinkedList.h"
#include "DSStack.h"
#include "DSAdjacencyList.h"

using namespace std;

TEST_CASE("DSLinkedList class", "[DSLinkedList]"){
    DSLinkedList<int> emptyListInt;
    DSLinkedList<DSString> emptyListString;
    DSLinkedList<int> oneElement(8);
    DSLinkedList<int> ascendingList;
    DSLinkedList<DSString> listofStrings;
    DSLinkedList<DSString> oneList("my string");

    for(int i = 0; i < 10; i++){
        ascendingList.insert(i);
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
        listofStrings.insert(testString[i]);
    }

    DSLinkedList<DSString> equalStringList;
    equalStringList = listofStrings;

    SECTION("getSize() check"){
        REQUIRE(emptyListInt.size() == 0);
        REQUIRE(oneElement.size() == 1);
        REQUIRE(ascendingList.size() == 10);
        REQUIRE(listofStrings.size() == 11);
        REQUIRE(oneList.size() == 1);
    }

    SECTION("[] operator check") {
        REQUIRE(ascendingList[2] == 2);
        REQUIRE(ascendingList[8] == oneElement[0]);
        REQUIRE(listofStrings[3] == "UPPERCASE STRING");
        DSString str = "my string";
        REQUIRE(oneList[0] == str);
    }

    SECTION("copy constructor check") {
        REQUIRE(equalStringList.size() == 11);
        REQUIRE(equalStringList[4] == "lower string");
        //DSLinkedList<int> integers1 = ascendingList;
        for (int i = 0; i < 10; i++) {
            REQUIRE(ascendingList[i] == i);
        }
        DSLinkedList<DSString> strings1 = emptyListString;
        REQUIRE(strings1.size() == 0);
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
        REQUIRE(testString.size() == 0);
        testString = oneList;
        REQUIRE(testString.size() == 1);
        DSLinkedList<int> integers1(4);
        ascendingList = integers1;
        REQUIRE(ascendingList.size() == 1);
        REQUIRE(ascendingList[0] == 4);
    }
    SECTION("add to end check") {
        emptyListInt.insert(3);
        REQUIRE(emptyListInt.size() == 1);
        REQUIRE(emptyListInt[0] == 3);
        DSString str = "UPPERCASE STRING";
        listofStrings.insert(str);
        REQUIRE(listofStrings.size() == 12);
        REQUIRE(listofStrings[11] == listofStrings[3]);
        oneList.insert("Los Angeles");
        oneList.insert("Los Angeles");
        REQUIRE(oneList[1] == oneList[2]);
    }
    SECTION("add to front check") {
        emptyListInt.addFront(3);
        REQUIRE(emptyListInt.size() == 1);
        REQUIRE(emptyListInt[0] == 3);
        DSString str = "UPPERCASE STRING";
        listofStrings.addFront(str);
        REQUIRE(listofStrings.size() == 12);
        REQUIRE(listofStrings[0] == listofStrings[4]);
        //REQUIRE(listofStrings[11] == "yo");
        DSString str1 = oneList[0];
        oneList.addFront("");
        oneList.addFront("");
        REQUIRE(oneList[0] == oneList[1]);
        REQUIRE(oneList[2] == str1);
    }

    SECTION("remove function check") {
        oneElement.remove(0);
        REQUIRE(oneElement.size() == 0);
        listofStrings.remove(10);
        listofStrings.remove(9);
        listofStrings.remove(8);
        REQUIRE(listofStrings.size() == 8);
        REQUIRE(listofStrings[listofStrings.size()-1] == "   tab1    tab2    tab3    ");
        DSString str = "UPPERCASE STRING";
        oneList.insert(str);
        oneList.insert(str);
        oneList.remove(oneList.size()-1);
        REQUIRE(oneList.size() == 2);
        REQUIRE(oneList[1] == str);
        equalStringList.remove(1);
        equalStringList.remove(1);
        REQUIRE(equalStringList.size() == 9);
        REQUIRE(equalStringList[1] == listofStrings[3]);
    }
    SECTION("clear function check") {
        ascendingList.emptyList();
        REQUIRE(ascendingList.size() == 0);
        listofStrings.emptyList();
        REQUIRE(listofStrings.size() == 0);
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
TEST_CASE("Adjacency class", "[adjacency]"){
    DSAdjacencyList adjList;
    DSVector<DSLinkedList<AirportCity>> testList;
    DSString city1 = "Dallas";
    DSString city2 = "Los Angeles";
    DSString city3 = "NY";
    DSString city4 = "Bali";
    DSString city5 = "Bora Bora";
    DSString city6 = "Seattle";
    DSString airline1 = "American";
    DSString airline2 = "United";
    DSString airline3 = "Spirit";
    DSString airline4 = "Alaskan";
    DSString airline5 = "British";
    DSString airline6 = "Qatar";
    double cost1 = 49;
    double cost2 = 24;
    double cost3 = 56;
    double cost4 = 676;
    double cost5 = 245;
    double cost6 = 23;
    int time1 = 302;
    int time2 = 234;
    int time3 = 134;
    int time4 = 245;
    int time5 = 45645;

    SECTION("adding node check") {
        adjList.addNode(city1, city2, cost1, time1, airline1);
        testList = adjList.getAdjList();
        REQUIRE(testList.getSize() == 1);
    }
    SECTION("size check") {
        adjList.addNode(city2, city5, cost2, time2, airline2);
        adjList.addNode(city6, city1, cost3, time3, airline3);
        adjList.addNode(city2, city3, cost4, time4, airline4);
        adjList.addNode(city3, city6, cost5, time5, airline5);
        testList = adjList.getAdjList();
        REQUIRE(testList.getSize() == 3);
    }
    SECTION("element check"){
        AirportCity dallas("Dallas");
        AirportCity path("Dallas", 400, 24, "American");
        for(int i = 0; i < testList.getSize(); i++){
            REQUIRE(dallas.getName() == "Dallas");
            REQUIRE(testList[0].get(0).getName() == "Dallas");
            REQUIRE(testList[1].get(0).getName() == "Los Angeles");
            REQUIRE(testList[3].get(4).getCost() == 676);
            REQUIRE(testList[3].get(6).getTime() == 23);
        }
        SECTION("empty"){
            testList.empty();
            REQUIRE(testList.getSize() == 0);
        }
    }
}
