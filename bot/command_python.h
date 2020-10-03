#ifndef BOT_COMMAND_PYTHON
#define BOT_COMMAND_PYTHON
#include <Python.h>

#include "bot/command.h"

namespace programadores {

class CommandPython: public Command {

  public:
    CommandPython();
    virtual ~CommandPython();
    virtual bool is_match(std::string_view str) const override;
    virtual absl::StatusOr<std::string> eval(std::string_view str) override;
};

}
#endif
