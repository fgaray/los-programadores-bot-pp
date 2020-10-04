#ifndef BOT_LOG
#define BOT_LOG

#include <memory>
#include "third_party/recordio/recordio.h"

#include "bot/proto/log.pb.h"
#include "tgbot/tgbot.h"
#include "absl/status/statusor.h"

namespace programadores {

class Log {
  public:
    static absl::StatusOr<std::unique_ptr<Log>> CreateLog();

    virtual ~Log();
    void log(TgBot::Message::Ptr message);
  private:
    std::unique_ptr<RecordWriter> _record_writer;
    Log(std::unique_ptr<RecordWriter> record_writer);
};

}

#endif
