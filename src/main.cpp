#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace {
constexpr int width = 960, height = 540, fps = 30, frames = 150;
constexpr float gravity = 420.0f;
struct Particle { float x, y, vx, vy; };

void rectangle(std::vector<unsigned char>& image, int x0, int y0, int x1, int y1,
               unsigned char r, unsigned char g, unsigned char b) {
    for (int y = std::max(0, y0); y < std::min(height, y1); ++y)
        for (int x = std::max(0, x0); x < std::min(width, x1); ++x) {
            const int i = (y * width + x) * 3;
            image[i] = r; image[i + 1] = g; image[i + 2] = b;
        }
}

void droplet(std::vector<unsigned char>& image, int cx, int cy) {
    for (int dy = -3; dy <= 3; ++dy)
        for (int dx = -3; dx <= 3; ++dx)
            if (dx * dx + dy * dy <= 9)
                rectangle(image, cx + dx, cy + dy, cx + dx + 1, cy + dy + 1, 166, 226, 255);
}
}

int main() {
    std::vector<unsigned char> image(width * height * 3);
    std::vector<Particle> particles;
    constexpr float dt = 1.0f / fps;
    for (int frame = 0; frame < frames; ++frame) {
        rectangle(image, 0, 0, width, height, 23, 40, 59);
        rectangle(image, 0, 462, width, height, 48, 86, 63);
        rectangle(image, 145, 442, 207, 462, 82, 91, 95);
        rectangle(image, 158, 421, 194, 445, 126, 137, 139);
        rectangle(image, 169, 412, 196, 422, 180, 190, 187);

        for (int n = 0; n < 5; ++n) {
            const float spread = static_cast<float>((frame * 5 + n) % 9 - 4);
            particles.push_back({190.0f, 415.0f, 230.0f + spread * 5.0f,
                                 -390.0f + spread * 5.0f});
        }
        for (auto& p : particles) {
            p.x += p.vx * dt;
            p.y += p.vy * dt + 0.5f * gravity * dt * dt;
            p.vy += gravity * dt;
            if (p.y < 462.0f) droplet(image, static_cast<int>(p.x), static_cast<int>(p.y));
        }
        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.y >= 462.0f || p.x >= width; }), particles.end());
        std::cout.write(reinterpret_cast<const char*>(image.data()), image.size());
        if (!std::cout) return 1;
    }
}
