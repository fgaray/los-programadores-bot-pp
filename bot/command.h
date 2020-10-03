#ifndef BOT_COMMAND
#define BOT_COMMAND

#include <string_view>
#include "absl/status/statusor.h"

namespace programadores {

class Command {
  public:
    virtual bool is_match(std::string_view str) const = 0;
    virtual absl::StatusOr<std::string> eval(std::string_view str) = 0;
    virtual void save_state();
};

}


#endif
