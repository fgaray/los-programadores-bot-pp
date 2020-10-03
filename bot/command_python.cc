#include "bot/command_python.h"

#include <sstream>
#include "absl/strings/str_split.h"
#include "absl/strings/str_join.h"

namespace {
std::vector<std::string_view> bannedStrs = {
  "run",
  "while"
};
}

namespace programadores {


CommandPython::CommandPython() {
  Py_Initialize();  
}

CommandPython::~CommandPython() {
  Py_Finalize();
}

bool CommandPython::is_match(std::string_view str) const {
  std::vector<std::string_view> v = absl::StrSplit(str, ' ');
  if (v.size() > 1 && v.at(0) == "python") {
    for (auto banned: bannedStrs) {
      if (absl::StrContains(str, banned)) {
        return false;
      }
    }
    return true;  
  }

  return false;
}

absl::StatusOr<std::string> CommandPython::eval(std::string_view str) {
  std::vector<std::string_view> v = absl::StrSplit(str, ' ');
  v.erase(v.begin()); // removes the first element, we know that is "python"
  std::string input = absl::StrJoin(v, " ");

  PyObject *moduleMainString = PyString_FromString("__main__");
  PyObject *moduleMain = PyImport_Import(moduleMainString);
  std::stringstream ss;
  ss << "from random import randint\n";
  ss << "from random import choice\n";
  ss << "from datetime import date\n";
  ss << "today = date.today()\n";
  ss << "\n";
  ss << "def run():\n";
  ss << "    return str(" << input << ")";
  PyRun_SimpleString(ss.str().c_str());
  PyObject *func = PyObject_GetAttrString(moduleMain, "run");
  PyObject *result = PyObject_CallObject(func, nullptr);
  const char* str_result = PyString_AsString(result);
  if (str_result) {
    return str_result;
  } else {
    PyErr_Print();
    PyErr_Clear();
    return absl::InternalError("Python Error");
  }
}

}
