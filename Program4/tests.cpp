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
    for(int i = 0; i < 10; i++){
        ascendingList.insertEnd(i);
    }
    SECTION("size check"){
        REQUIRE(emptyList.getSize() == 0);
        REQUIRE(oneElement.getSize() == 1);
        REQUIRE(ascendingList.getSize() == 10);
    }
}
