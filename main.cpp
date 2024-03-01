#include <iostream>
#include "ReadInput.h"
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    ReadInput Map(n, m);
    getchar();
    Map.passMap();
    Map.passAirConnetions();
    Map.operateQuestions();

    return 0;
}

