#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace {
constexpr int width = 960, height = 540, fps = 30, frames = 150;
constexpr float gravity = 420.0f;
struct Particle { float x, y, z, vx, vy, vz; };

void rectangle(std::vector<unsigned char>& image, int x0, int y0, int x1, int y1,
               unsigned char r, unsigned char g, unsigned char b) {
    for (int y = std::max(0, y0); y < std::min(height, y1); ++y)
        for (int x = std::max(0, x0); x < std::min(width, x1); ++x) {
            const int i = (y * width + x) * 3;
            image[i] = r; image[i + 1] = g; image[i + 2] = b;
        }
}

void droplet(std::vector<unsigned char>& image, int cx, int cy) {
    for (int dy = -2; dy <= 2; ++dy)
        for (int dx = -2; dx <= 2; ++dx)
            if (dx * dx + dy * dy <= 4)
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
        rectangle(image, 449, 442, 511, 462, 82, 91, 95);
        rectangle(image, 462, 421, 498, 445, 126, 137, 139);
        rectangle(image, 467, 412, 493, 422, 180, 190, 187);

        // Sweep at a constant rate, then return to the left for the next pass.
        // The two jets sweep in opposite directions from separate nozzles.
        for (int n = 0; n < 6; ++n) {
            const float time = (frame + n / 6.0f) * dt;
            const float sweep = 2.0f * std::fmod(time, 2.0f) / 2.0f - 1.0f;
            for (float offset : {-10.0f, 10.0f}) {
                particles.push_back({480.0f + offset, 415.0f, 0.0f,
                    220.0f * sweep * (offset < 0.0f ? 1.0f : -1.0f), -390.0f, 0.0f});
            }
        }
        for (auto& p : particles) {
            p.x += p.vx * dt;
            p.y += p.vy * dt + 0.5f * gravity * dt * dt;
            p.z += p.vz * dt;
            p.vy += gravity * dt;
            // A simple oblique projection makes the depth component visible.
            if (p.y < 462.0f)
                droplet(image, static_cast<int>(p.x + 0.45f * p.z),
                        static_cast<int>(p.y - 0.25f * p.z));
        }
        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.y >= 462.0f; }), particles.end());
        std::cout.write(reinterpret_cast<const char*>(image.data()), image.size());
        if (!std::cout) return 1;
    }
}
