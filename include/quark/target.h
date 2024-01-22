#ifndef QUARK_TARGET_H
#define QUARK_TARGET_H

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace quark {

enum struct OptLevel : std::uint8_t { None, Balance, Speed, Size };

struct Target {
    enum struct Type : std::uint8_t { App, Library };

    std::string name;
    Type type;

    OptLevel opt_level;

    std::uint8_t cpp_std;
    std::uint8_t c_std;

    std::vector<std::filesystem::path> includes;
    std::vector<std::filesystem::path> sources;
};

} // namespace quark

#endif
