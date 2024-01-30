/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file message.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 13:59:28
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_MESSAGE_H
#define RINA_MESSAGE_H

#include <string>
#include <memory>

namespace rina {

class Message {
public:
  Message() {}

  virtual ~Message() {}

  virtual const std::string& type() = 0;

  virtual std::string to_string() = 0;
}; // class Message

using message_ptr_t = std::shared_ptr<Message>;

class SystemMessage : public Message {
public:
  virtual const std::string& type() {
    static const std::string _type = "system";
    return _type;
  }

  virtual std::string to_string() {
    return "not implemented";
  }
}; // class SystemMessage

using system_message_ptr_t = std::shared_ptr<SystemMessage>;

class ChatMessage : public Message {
public:
  ChatMessage() {}
  
  ChatMessage(const std::string& role, const std::string& content)
    : _role(role), _content(content) {}

  virtual ~ChatMessage() {}

  virtual const std::string& type() {
    static const std::string _type = "chat";
    return _type;
  }

  virtual std::string to_string() {
    return "not implemented";
  }

  const std::string& role() const {
    return _role;
  }

  const std::string& content() const {
    return _content;
  }

  void set(const std::string& role, const std::string& content) {
    _role = role;
    _content = content;
  }

private:
  std::string _role;
  std::string _content;
}; // class ChatMessage

using chat_message_ptr_t = std::shared_ptr<ChatMessage>;

class FunctionMessage : public Message {
public:
  virtual const std::string& type() {
    static const std::string _type = "function";
    return _type;
  }

  virtual std::string to_string() {
    return "not implemented";
  }
}; // class FunctionMessage

using function_message_ptr_t = std::shared_ptr<FunctionMessage>;

} // namespace rina

#endif  //RINA_MESSAGE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
