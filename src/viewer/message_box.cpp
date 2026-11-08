#include "viewer/message_box.hpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

namespace swarm::viewer {

void showFatalMessage(const std::string& text) {
#ifdef _WIN32
    constexpr size_t MAX_CHARS = 3000;
    const std::string shown = text.size() > MAX_CHARS ? text.substr(0, MAX_CHARS) + "\n\n(cut here; the console shows the whole message)" : text;
    const int n = MultiByteToWideChar(CP_UTF8, 0, shown.c_str(), -1, nullptr, 0);
    if (n <= 0) return;
    std::wstring wide(size_t(n), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, shown.c_str(), -1, wide.data(), n);
    MessageBoxW(nullptr, wide.c_str(), L"S.W.A.R.M.", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
#else
    (void)text;
#endif
}

} // namespace swarm::viewer
