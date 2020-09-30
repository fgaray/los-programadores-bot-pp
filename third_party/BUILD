load("@rules_cc//cc:defs.bzl", "cc_library") 

cc_library(
    name = "tgbot",
    srcs = glob(["tgbot-cpp/src/**/*.cpp"]),
    hdrs = glob(["tgbot-cpp/include/**/*"]),
    strip_include_prefix = "tgbot-cpp/include",
		deps = ["@boost//:system"],
		copts = ["-std=c++17"],
	  visibility = ["//visibility:public"],
)
