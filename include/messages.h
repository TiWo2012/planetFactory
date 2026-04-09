#pragma once

enum class MessageType {
  None,
  GameOver,
};

class Messages {
public:
  Messages();
  ~Messages();

  void        setMessage(MessageType t);
  MessageType getMessage() const;

private:
  MessageType message = MessageType::None;
};
