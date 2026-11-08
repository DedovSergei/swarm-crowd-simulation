#include <swarm/assets.hpp>

#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace swarm {

namespace {

fs::path executableDir() {
#ifdef _WIN32
    std::wstring buf(MAX_PATH, L'\0');
    for (;;) {
        DWORD n = GetModuleFileNameW(nullptr, buf.data(), static_cast<DWORD>(buf.size()));
        if (n == 0) return {};
        if (n < buf.size()) { buf.resize(n); break; }
        buf.resize(buf.size() * 2); // truncated: retry with a larger buffer
    }
    return fs::path(buf).parent_path();
#else
    std::error_code ec;
    fs::path exe = fs::read_symlink("/proc/self/exe", ec);
    return ec ? fs::path{} : exe.parent_path();
#endif
}

} // namespace

fs::path executableDirectory() { return executableDir(); }

fs::path processTempPath(const std::string& name) {
#ifdef _WIN32
    const unsigned long pid = GetCurrentProcessId();
#else
    const unsigned long pid = 0;
#endif
    return fs::temp_directory_path() / (name + "_" + std::to_string(pid));
}

fs::path resolveAsset(const fs::path& relative) {
    std::vector<fs::path> roots;
    if (fs::path exe = executableDir(); !exe.empty()) roots.push_back(exe);
    std::error_code ec;
    if (fs::path cwd = fs::current_path(ec); !ec) roots.push_back(cwd);
#ifdef SWARM_SOURCE_DIR
    roots.push_back(fs::path(SWARM_SOURCE_DIR));
#endif

    std::string tried;
    for (const fs::path& root : roots) {
        fs::path candidate = root / relative;
        if (fs::exists(candidate, ec)) return candidate;
        tried += "\n  " + candidate.string();
    }
    throw std::runtime_error("Asset not found: " + relative.string() + " (searched:" + tried + ")");
}

} // namespace swarm
