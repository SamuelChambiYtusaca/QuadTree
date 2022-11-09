#include "QT.hpp"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

int main(){
    srand(time(NULL));
    vector<string> names = {
        "Peru",
        "Argentina",
        "Brasil",
        "Colombia",
        "Chile",
        "Venezuela",
        "Bolivia",
        "Paraguay",
        "Uruguay",
        "Ecuador"
    };
    QT<int> quadtree;
    for(int i = 0; i < 50; i++){
        int x = 1 + rand()%100;
        int y = 1 + rand()%100;
        int val = 1 + rand()%120;
        quadtree.insert(x,y,val);
    }
    quadtree.search(1,100, 100,1);
    quadtree.graph("salida2.dot");
    return 0;
}