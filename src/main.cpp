#include <iostream>

constexpr int IMAGE_WIDTH = 200;
constexpr int IMAGE_HEIGHT = 100;

int main() {
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            float r = static_cast<float>(i) / static_cast<float>(IMAGE_WIDTH);
            float g = static_cast<float>(j) / static_cast<float>(IMAGE_HEIGHT);
            float b = 0.2f; 
            int ir = static_cast<int>(255.99f * r);
            int ig = static_cast<int>(255.99f * g);
            int ib = static_cast<int>(255.99f * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}