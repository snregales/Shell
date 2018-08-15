#include "testing.hpp"

#ifdef CATCH_CONFIG_MAIN
#include "catch.hpp"
/*______Shell_Test_Cases___________________________________________________________________*/
TEST_CASE("Shell"){
    SECTION("Singleton"){
        REQUIRE(true);
    }
}
/*______Queue_Test_Cases____________________________________________________________*/
#include <string.h>
#include "Queue.hpp"

template<class T>
void
clear(T &container){
    while(!container.empty()){
        container.pop();
    }
}

void
manager_helper(Queue &container, char *&input, int size, bool erase = true){
    CHECK(container.empty());
    container.manager(input);
    REQUIRE(int(container.size()) == size);
    if(erase) clear(container);
}

TEST_CASE("Queue", "[input, char*, queque]"){
    char *input = new char[1024];
    Queue container = Queue();
    SECTION("manager", "[strpbrk, parser, char*]"){
/*______Test_managers_deligation_____________________________________________________________*/
        strcpy(input, "Sharlon Natividad Regales");
        manager_helper(container, input, 3);
/*______Test_managers_deligation_____________________________________________________________*/
        strcpy(input, "Sharlon; Natividad; Regales:Angela");
        manager_helper(container, input, 3);
    }
    SECTION("pop","[char*, container]"){
/*______Test_container_order_________________________________________________________________*/
        std::string mouse = "mouse", catches = "catches", cat = "cat";
        strcpy(input, (mouse+" "+catches+" "+cat).c_str());
        manager_helper(container, input, 3, false);
        REQUIRE(std::string(container.pop()) == mouse);
        REQUIRE(std::string(container.pop()) == catches);
        REQUIRE(std::string(container.pop()) == cat);    
        CHECK(container.empty());
    }
    SECTION("manager", "[deligate]"){
        strcpy(input, "cd Dev/CPP; nano catch.hpp; EXIT");
        container.manager(input);
        int size = (int) container.size();
        REQUIRE(size == 3);
        char *temp;
        while(size){
            temp = container.pop();
            container.manager(temp);
            size--;
        }
        REQUIRE(int(container.size()) == 5);     
    }
    delete input;
}

#endif