load("@rules_cc//cc:defs.bzl", "cc_binary") 

COPTS = ["-std=c++17 -Wno-reorder"]

cc_binary(
  name = "main",
  srcs = ["main.cc"],
  copts = COPTS,
  deps = [
      "//third_party:tgbot",
  ],
  linkopts = ["-pthread -lssl -lcrypto"],
)
