load("@rules_cc//cc:defs.bzl", "cc_binary") 

COPTS = ["-Wno-reorder"]

cc_binary(
  name = "main",
  srcs = ["main.cc"],
  copts = COPTS,
  deps = [
      "//third_party:tgbot",
      "@com_google_absl//absl/status:statusor",
      "@com_google_absl//absl/status:status",
      "@com_google_absl//absl/flags:parse",
      ":command",
      ":command-python",
      ":log",
  ],
  linkopts = ["-pthread -lssl -lcrypto"],
)

cc_library(
  name = "command-python",
  srcs = ["command_python.cc"],
  hdrs = ["command_python.h"],
  deps = [
      "@pybind11//:pybind11_embed",
      "@com_google_absl//absl/strings",
      ":command",
  ],
)

cc_library(
  name = "command",
  srcs = ["command.cc"],
  hdrs = ["command.h"],
  deps = [
      "@com_google_absl//absl/status:statusor",
  ],
)

cc_library(
  name = "log",
  srcs = ["log.cc"],
  hdrs = ["log.h"],
  deps = [
      "//bot/proto:log_cc_proto",
      "//third_party:tgbot",
      "//third_party/base:recordio",
      "@com_google_absl//absl/status:statusor",
  ],
)
