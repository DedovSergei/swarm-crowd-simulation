#include "viewer/legend.hpp"

#include "viewer/palette.hpp"
#include "viewer/scales.hpp"

#include <swarm/metrics.hpp>

#include <imgui.h>

#include <algorithm>
#include <cstdio>

namespace swarm::viewer {

using namespace palette;

namespace {
void swatch(uint32_t hex, const char* text) {
    const float h = ImGui::GetTextLineHeight();
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x, p.y + 0.15f * h), ImVec2(p.x + h, p.y + 0.85f * h), rgb(hex), 2.0f);
    ImGui::Dummy(ImVec2(h, h));
    ImGui::SameLine();
    ImGui::TextUnformatted(text);
}
} // namespace

void drawScaleLegend(const ColourScale& scale, const char* title, bool zeroSwatch, const char* noDataText) {
    const float s = ImGui::GetStyle().FontScaleDpi;
    const float lineH = ImGui::GetTextLineHeight();
    ImGui::Text("%s [%s]", title, scale.unit);
    if (ImGui::IsItemHovered() && ImGui::BeginTooltip()) {   // wrapped: the notes are single lines (they also go into the export's JSON)
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 40.0f);
        ImGui::Text("Fixed scale: %s", scale.rangeNote);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }

    const float w = ImGui::GetContentRegionAvail().x;
    const float margin = 0.5f * ImGui::CalcTextSize("1000+").x;   // room for the end labels
    const ImVec2 p0 = ImGui::GetCursorScreenPos();
    const ImVec2 a(p0.x + margin, p0.y), b(p0.x + w - margin, p0.y + 14.0f * s);
    bool twoLines = false;
    for (int i = 0; i < scale.tickCount; ++i) twoLines |= scale.ticks[i].note != nullptr;
    ImGui::Dummy(ImVec2(w, (b.y - a.y) + 4.0f * s + lineH * (twoLines ? 2.0f : 1.0f)));
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const float seg = (b.x - a.x) / float(RAMP_STEPS - 1);
    for (int i = 0; i + 1 < RAMP_STEPS; ++i) {
        const float x0 = a.x + seg * float(i), x1 = a.x + seg * float(i + 1);
        dl->AddRectFilledMultiColor(ImVec2(x0, a.y), ImVec2(x1 + 0.5f, b.y), rgb(RAMP[i]), rgb(RAMP[i + 1]), rgb(RAMP[i + 1]), rgb(RAMP[i]));
    }
    for (int i = 0; i < scale.tickCount; ++i) {
        const ScaleTick& t = scale.ticks[i];
        const float x = a.x + (b.x - a.x) * scale.t(t.value);
        dl->AddLine(ImVec2(x, a.y), ImVec2(x, b.y + 3.0f * s), rgb(TEXT_SECONDARY_DARK), 1.0f);
        const float lw = ImGui::CalcTextSize(t.label).x;
        dl->AddText(ImVec2(x - 0.5f * lw, b.y + 3.0f * s), rgb(TEXT_SECONDARY_DARK), t.label);
        if (t.note) {
            const float nw = ImGui::CalcTextSize(t.note).x;
            dl->AddText(ImVec2(x - 0.5f * nw, b.y + 3.0f * s + lineH), rgb(MUTED), t.note);
        }
    }
    if (zeroSwatch) {
        swatch(ZERO, "walkable floor, value 0");
    }
    if (noDataText) {
        ImGui::PushStyleColor(ImGuiCol_Text, rgb(MUTED));
        ImGui::TextWrapped("%s", noDataText);
        ImGui::PopStyleColor();
    }
}

void drawZoneLegend() {
    ImGui::TextUnformatted("Zone (metrics zones, per position)");
    if (ImGui::BeginTable("zones", 3)) {
        for (int z = 0; z < ZONE_COLOURS; ++z) {
            ImGui::TableNextColumn();
            swatch(ZONE[z], metrics::zoneName(uint32_t(z)));
        }
        ImGui::EndTable();
    }
}

} // namespace swarm::viewer
