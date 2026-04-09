#include "messages.h"

Messages::Messages()  = default;
Messages::~Messages() = default;

void Messages::setMessage(MessageType t) {
  message = t;
}

MessageType Messages::getMessage() const {
  return message;
}
