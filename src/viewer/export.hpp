#pragma once

// Figure export of the viewer: an offscreen framebuffer, a one-off pixel read and PNG files.
// These user-triggered framebuffer reads (screenshot, heatmap export, the self-test) are the only
// readbacks the viewer makes besides the fence-gated counters; each waits for the GPU once, on demand.

#include <glad/glad.h>

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace swarm::viewer {

// RGBA8 colour + 24-bit depth renderbuffers; bind() makes it the draw and read framebuffer with a full viewport
class OffscreenTarget {
public:
    OffscreenTarget(int width, int height);
    ~OffscreenTarget();
    OffscreenTarget(const OffscreenTarget&) = delete;
    OffscreenTarget& operator=(const OffscreenTarget&) = delete;
    void bind() const;
    int width() const { return w_; }
    int height() const { return h_; }
    // Reads the colour attachment as tightly packed RGB rows, bottom row first (OpenGL order). Waits for the GPU.
    std::vector<uint8_t> readRGB() const;

private:
    int w_, h_;
    GLuint fbo_ = 0, colour_ = 0, depth_ = 0;
};

// The largest square export the GL allows (min of GL_MAX_RENDERBUFFER_SIZE and GL_MAX_VIEWPORT_DIMS)
int maxExportSize();

// PNG of tightly packed RGB rows given bottom row first (flipped to the usual top-first order). Throws on failure.
void writePngRGB(const std::filesystem::path& path, int width, int height, const std::vector<uint8_t>& rgbBottomUp);

// "<venue>_N<n>_t<seconds>s_<commit>[_<suffix>]", e.g. stadium_N4096_t87.5s_9d8cb84
std::string exportStem(const std::string& venue, int n, double simTimeS, const std::string& commit, const std::string& suffix = {});
// dir / (stem + ext), or dir / (stem + "_2" + ext), "_3", ... if it exists
std::filesystem::path uniquePath(const std::filesystem::path& dir, const std::string& stem, const std::string& ext);

} // namespace swarm::viewer
