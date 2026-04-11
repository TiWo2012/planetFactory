#pragma once

enum class MessageType {
  None,
  GameOver,
};

class Messages {
public:
  Messages(MessageType initial = MessageType::None);
  ~Messages();

  void        setMessage(MessageType t);
  MessageType getMessage() const;

private:
  MessageType message;
};
