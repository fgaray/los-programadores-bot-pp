# Los programadores bot

A telegram bot for a private chat


# Getting started

You need to have bazel installed, then clone the repository

```
  git clone --recursive git@github.com:fgaray/los-programadores-bot-pp.git
```

# Compilation

```
  bazel build //bot:main
```

# Running

```
  TOKEN=YOURTOKEN bazel run //bot:main
```
