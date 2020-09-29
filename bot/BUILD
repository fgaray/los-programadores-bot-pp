load("@rules_cc//cc:defs.bzl", "cc_binary") 

COPTS = ["-std=c++17 -Wall -Werror -pedantic -pedantic-errors -Wuninitialized -Wno-error=unused-variable"]

cc_binary(
  name = "main",
  srcs = ["main.cc"],
  copts = COPTS,
)
