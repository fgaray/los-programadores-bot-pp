#include <iostream>
#include "tgbot/tgbot.h"


int main() {
  const char* token = std::getenv("TOKEN");
  if (!token) {
    std::cerr << "Set the TOKEN enviroment variable" << std::endl;
    return -1;
  }
  TgBot::Bot bot(token);

  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    std::cout << "ECHO " << message->text << std::endl;
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
