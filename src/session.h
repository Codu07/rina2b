/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file session.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/01 22:03:42
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_SESSION_H
#define RINA_SESSION_H

#include <string>
#include <memory>
#include <unordered_map>

#include "context.h"

namespace rina {

class Session {
public:
  Session(const std::string& sid) 
    : _sid(sid),
      _ctx(std::make_shared<Context>()) {}

  ~Session() {}

  const std::string& sid() const {
    return _sid;
  }

  context_ptr_t& ctx() {
    return _ctx;
  }

private:
  std::string _sid;
  context_ptr_t _ctx;
}; // class Session

using session_ptr_t = std::shared_ptr<Session>;

class SessionManager {
public:
  static SessionManager* instance();

public:
  ~SessionManager() {}

  int init();

  int destroy();

  session_ptr_t new_session();

  session_ptr_t get_session(const std::string& sid);

private:
  SessionManager() {}
  SessionManager(const SessionManager&) = delete;

private:
  std::unordered_map<std::string, session_ptr_t> _sessions;
}; // class SessionManager

}; // namespace rina

#endif  //RINA_SESSION_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
