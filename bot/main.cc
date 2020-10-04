#include <iostream>
#include <memory>
#include <vector>
#include "tgbot/tgbot.h"
#include "bot/command.h"
#include "bot/command_python.h"
#include "bot/log.h"
#include "absl/status/statusor.h"
using namespace programadores;

int main() {
  const char* token = std::getenv("TOKEN");
  if (!token) {
    std::cerr << "Set the TOKEN enviroment variable" << std::endl;
    return -1;
  }
  // The commands
  
  std::vector<std::unique_ptr<Command>> commands;
  commands.push_back(std::make_unique<CommandPython>());


  // The bot
  TgBot::Bot bot(token);
  absl::StatusOr<std::unique_ptr<Log>> logger = Log::CreateLog();
  if (!logger.ok()) {
    std::cerr << "Error: " << logger.status().message() << std::endl;
    return -1;
  }

  bot.getEvents().onAnyMessage([&bot, &commands, &logger](TgBot::Message::Ptr message) {
    // we log everything
    (*logger)->log(message);
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
    TgBot::TgLongPoll poll(bot);
    while (true) {
      poll.start();
    }
  } catch (TgBot::TgException& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
