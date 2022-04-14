#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include "tgbot/tgbot.h"
#include "bot/command.h"
#include "bot/command_python.h"
#include "bot/log.h"
#include "absl/status/statusor.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
using namespace programadores;

ABSL_FLAG(std::string, token, "YOUR_TOKEN", "The Telegram's token bot");
ABSL_FLAG(std::string, storage_path, ".", "Where to store the logs");

static std::unique_ptr<Log> logger;

void SetupHandlers() {
  std::signal(SIGINT, [](int signal) {
    delete logger.get();
    logger.release();
    exit(-1);
  });
}

int main(int argc, char *argv[]) {
  absl::ParseCommandLine(argc, argv);
  
  std::vector<std::unique_ptr<Command>> commands;

  // The bot
  TgBot::Bot bot(absl::GetFlag(FLAGS_token));
  absl::StatusOr<std::unique_ptr<Log>> logger_or = Log::CreateLog(absl::GetFlag(FLAGS_storage_path));
  if (!logger_or.ok()) {
    std::cerr << "Error: " << logger_or.status().message() << std::endl;
    return -1;
  }

  logger = std::move(*logger_or);
  SetupHandlers();

  bot.getEvents().onAnyMessage([&bot, &commands, &logger](TgBot::Message::Ptr message) {
    // we log everything
    logger->log(message);
    for (auto &command: commands) {
      if (command->is_match(message->text)) {
        absl::StatusOr<std::string> result = command->eval(message->text);
        if (result.ok()) {
          // send message back to the same chat
          bot.getApi().sendMessage(message->chat->id, result.value());
        } else {
          std::cerr << "Error: " << result.status().message() << std::endl;
          bot.getApi().sendMessage(message->chat->id, std::string(result.status().message()));
        }
      }
    }
  });


  // run the bot
  try {
    std::cout << "Running..." << std::endl;
    std::cout << "Storing logs in: " << absl::GetFlag(FLAGS_storage_path) << std::endl;
    TgBot::TgLongPoll poll(bot);
    while (true) {
      poll.start();
    }
  } catch (TgBot::TgException& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
