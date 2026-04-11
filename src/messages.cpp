#include "messages.h"

Messages::Messages(MessageType initial) : message(initial) {}
Messages::~Messages() = default;

void Messages::setMessage(MessageType t) {
  message = t;
}

MessageType Messages::getMessage() const {
  return message;
}
