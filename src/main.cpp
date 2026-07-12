#include <iostream>
#include "vec3.h"

int main() {
    constexpr int nx = 200;
    constexpr int ny = 100;

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            // Usando a classe vec3
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2f);
            
            int ir = static_cast<int>(255.99f * col[0]);
            int ig = static_cast<int>(255.99f * col[1]);
            int ib = static_cast<int>(255.99f * col[2]);
            
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}