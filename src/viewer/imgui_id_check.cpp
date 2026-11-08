#include "viewer/imgui_id_check.hpp"

#include <imgui.h>
#include <imgui_internal.h>

#include <cstdio>
#include <unordered_map>

namespace swarm::viewer::idcheck {

namespace {
bool g_on = false;
int g_conflicts = 0;
std::unordered_map<ImGuiID, int> g_lastFrame;      // the frame each ID was last submitted in
std::unordered_map<ImGuiID, std::string> g_labels; // from the item-info hook
std::vector<ImGuiID> g_conflictIds;
} // namespace

void setEnabled(bool on) {
    g_on = on;
    g_conflicts = 0;
    g_lastFrame.clear();
    g_conflictIds.clear();
    if (ImGuiContext* ctx = ImGui::GetCurrentContext()) ctx->TestEngineHookItems = on;
}

int conflicts() { return g_conflicts; }

std::vector<std::string> samples() {
    std::vector<std::string> out;
    for (ImGuiID id : g_conflictIds) {
        const auto it = g_labels.find(id);
        if (it != g_labels.end()) { out.push_back(it->second); continue; }
        char b[24];
        std::snprintf(b, sizeof b, "id 0x%08x", unsigned(id));
        out.emplace_back(b);
    }
    return out;
}

} // namespace swarm::viewer::idcheck

// --- Dear ImGui's test-engine hooks (imgui_internal.h; called only while ctx->TestEngineHookItems) ---
using namespace swarm::viewer::idcheck;

void ImGuiTestEngineHook_ItemAdd(ImGuiContext* ctx, ImGuiID id, const ImRect&, const ImGuiLastItemData* item) {
    // Whole windows come without item data (a window may be begun twice in a frame: appended to)
    if (!g_on || id == 0 || item == nullptr || (item->ItemFlags & ImGuiItemFlags_AllowDuplicateId) != 0) return;
    const auto [it, inserted] = g_lastFrame.try_emplace(id, ctx->FrameCount);
    if (inserted) return;
    if (it->second == ctx->FrameCount) {
        ++g_conflicts;
        if (g_conflictIds.size() < 8) g_conflictIds.push_back(id);
    }
    it->second = ctx->FrameCount;
}

void ImGuiTestEngineHook_ItemInfo(ImGuiContext*, ImGuiID id, const char* label, ImGuiItemStatusFlags) {
    if (g_on && id != 0 && label != nullptr) g_labels[id] = label;
}

void ImGuiTestEngineHook_Log(ImGuiContext*, const char*, ...) {}

const char* ImGuiTestEngine_FindItemDebugLabel(ImGuiContext*, ImGuiID id) {
    const auto it = g_labels.find(id);
    return it == g_labels.end() ? nullptr : it->second.c_str();
}
