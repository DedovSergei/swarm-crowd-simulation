#pragma once

#include <string>

namespace swarm::viewer {

// A modal error box (Windows; elsewhere nothing: the console has the message). Long texts, a driver's compile log, are cut.
void showFatalMessage(const std::string& text);

} // namespace swarm::viewer
