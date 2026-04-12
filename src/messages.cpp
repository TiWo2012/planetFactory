/**
 * @file messages.cpp
 * @brief Implementation of the game message system
 *
 * This file implements the Messages class, which manages game state messages
 * such as game over notifications. It provides a simple interface for setting
 * and retrieving the current message type.
 */

#include "messages.h"

/**
 * @brief Construct a Messages object with initial message type
 * @param initial Initial message type
 */
Messages::Messages(MessageType initial) : message(initial) {}

/**
 * @brief Destroy the Messages object
 */
Messages::~Messages() = default;

/**
 * @brief Set the current message type
 * @param t New message type
 */
void Messages::setMessage(MessageType t) {
  message = t;
}

/**
 * @brief Get the current message type
 * @return Current message type
 */
MessageType Messages::getMessage() const {
  return message;
}
