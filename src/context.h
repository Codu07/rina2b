/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file context.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 14:17:21
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_CONTEXT_H
#define RINA_CONTEXT_H

#include <memory>
#include <string>
#include <vector>

#include "message.h"

namespace rina {

class Context {
public:
  Context() {}

  ~Context() {}

  int init(system_message_ptr_t system_message) {
    this->set_system_message(system_message);
    _initialized = true;
    return 0;
  }

  bool is_initialized() const {
    return _initialized;
  }

  system_message_ptr_t& system_message() {
    return _system_message;
  }

  void set_system_message(system_message_ptr_t system_message) {
    _system_message = system_message;
  }

  std::vector<message_ptr_t>& history() {
    return _history;
  }

  void append_history(message_ptr_t message) {
    _history.emplace_back(message);
  }

private:
  bool _initialized {false};
  system_message_ptr_t _system_message;
  std::vector<message_ptr_t> _history; 
}; // class Context

using context_ptr_t = std::shared_ptr<Context>;

} // namespace rina

#endif  //RINA_CONTEXT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
