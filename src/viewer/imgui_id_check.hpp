#pragma once

// Dear ImGui ID-conflict detection for SWARM --selftest-ui. Two widgets with the same ID (the same label in
// the same ID scope) share their state. ImGui reports a conflict only for the item under the mouse (io.ConfigDebugHighlightIdConflicts), and the
// self-test's hidden window has no mouse, so this counts them itself: through ImGui's test-engine item hooks
// (IMGUI_ENABLE_TEST_ENGINE, a compile definition of the imgui target; the hooks run only while enabled), every item
// submitted with an ID that another item already used in the same frame is a conflict.

#include <string>
#include <vector>

namespace swarm::viewer::idcheck {

// Starts (or stops) counting in the current ImGui context, from zero
void setEnabled(bool on);
// Conflicts counted since enabled, and the labels of the first few (label unknown: the hex ID)
int conflicts();
std::vector<std::string> samples();

} // namespace swarm::viewer::idcheck
