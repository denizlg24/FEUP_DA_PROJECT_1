//
// Created by deniz on 3/17/2025.
//
#include "data_structures/MapFactory.h"
int main() {
    auto* factory = new MapFactory();
    printf("Pointer to new map = %p",factory->getMap());
    return 0;
}
