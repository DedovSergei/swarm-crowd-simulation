#include "viewer/export.hpp"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <stdexcept>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WRITE_NO_STDIO   // written through std::ofstream (wide paths on Windows), not fopen
#include <stb_image_write.h>

namespace swarm::viewer {

OffscreenTarget::OffscreenTarget(int width, int height) : w_(width), h_(height) {
    if (width <= 0 || height <= 0 || std::max(width, height) > maxExportSize())
        throw std::runtime_error("offscreen target " + std::to_string(width) + " x " + std::to_string(height) + " exceeds the GL limits (" +
                                 std::to_string(maxExportSize()) + ")");
    glGenRenderbuffers(1, &colour_);
    glBindRenderbuffer(GL_RENDERBUFFER, colour_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
    glGenRenderbuffers(1, &depth_);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colour_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_);
    const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        glDeleteFramebuffers(1, &fbo_);
        glDeleteRenderbuffers(1, &colour_);
        glDeleteRenderbuffers(1, &depth_);
        throw std::runtime_error("offscreen framebuffer incomplete (status 0x" + std::to_string(status) + ")");
    }
}

OffscreenTarget::~OffscreenTarget() {
    glDeleteFramebuffers(1, &fbo_);
    glDeleteRenderbuffers(1, &colour_);
    glDeleteRenderbuffers(1, &depth_);
}

void OffscreenTarget::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    glViewport(0, 0, w_, h_);
}

std::vector<uint8_t> OffscreenTarget::readRGB() const {
    std::vector<uint8_t> px(size_t(w_) * size_t(h_) * 3);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    GLint oldPack = 4;
    glGetIntegerv(GL_PACK_ALIGNMENT, &oldPack);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, w_, h_, GL_RGB, GL_UNSIGNED_BYTE, px.data());   // one-off, user-triggered: waits for the GPU
    glPixelStorei(GL_PACK_ALIGNMENT, oldPack);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    return px;
}

int maxExportSize() {
    GLint rb = 0, vp[2] = { 0, 0 };
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &rb);
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, vp);
    return std::min({ int(rb), int(vp[0]), int(vp[1]) });
}

void writePngRGB(const std::filesystem::path& path, int width, int height, const std::vector<uint8_t>& rgbBottomUp) {
    if (rgbBottomUp.size() != size_t(width) * size_t(height) * 3) throw std::invalid_argument("writePngRGB: pixel buffer size");
    if (path.has_parent_path()) std::filesystem::create_directories(path.parent_path());
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("cannot write " + path.string());
    auto sink = [](void* ctx, void* data, int size) { static_cast<std::ofstream*>(ctx)->write(static_cast<const char*>(data), size); };
    stbi_flip_vertically_on_write(1);   // top-down PNG rows from OpenGL's bottom-up order
    const bool ok = stbi_write_png_to_func(sink, &out, width, height, 3, rgbBottomUp.data(), width * 3) != 0;
    stbi_flip_vertically_on_write(0);
    if (!ok || !out) throw std::runtime_error("PNG encoding failed for " + path.string());
}

std::string exportStem(const std::string& venue, int n, double simTimeS, const std::string& commit, const std::string& suffix) {
    char buf[256];
    std::snprintf(buf, sizeof(buf), "%s_N%d_t%.1fs_%s%s%s", venue.c_str(), n, simTimeS, commit.c_str(), suffix.empty() ? "" : "_",
                  suffix.c_str());
    return buf;
}

std::filesystem::path uniquePath(const std::filesystem::path& dir, const std::string& stem, const std::string& ext) {
    std::filesystem::path p = dir / (stem + ext);
    for (int k = 2; std::filesystem::exists(p); ++k) p = dir / (stem + "_" + std::to_string(k) + ext);
    return p;
}

} // namespace swarm::viewer
