#include "bot/log.h"

namespace programadores {

absl::StatusOr<std::unique_ptr<Log>> Log::CreateLog(const std::string &path) {
  File* file = File::Open(path + "/log.recordio", "w");
  if (!file) {
    return absl::InternalError("Can't open log.recordio for write in path " + path);
  }

  std::unique_ptr<recordio::RecordWriter> record_writer = std::make_unique<recordio::RecordWriter>(file);
  std::unique_ptr<Log> log(new Log(std::move(record_writer)));
  return log;
}

Log::Log(std::unique_ptr<recordio::RecordWriter> record_writer): _record_writer(std::move(record_writer)) {

}

Log::~Log() {
  _record_writer->Close();
  std::cout << "closing" << std::endl;
}

void Log::log(TgBot::Message::Ptr message_ptr) {
  if (!message_ptr) {
    return;
  }
  Message message;
  message.set_user_id(message_ptr->from->id);
  message.set_user_name(message_ptr->from->firstName);
  message.set_id(message_ptr->messageId);
  message.set_text(message_ptr->text);
  message.set_date(message_ptr->date);
  message.set_chat_id(message_ptr->chat->id);
  _record_writer->WriteProtocolMessage(message);
}


} // namespace programadores
