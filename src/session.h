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
#include <map>

namespace rina {

class Session {
public:
  Session(const std::string& sid) : _sid(sid) {}

  ~Session() {}

  const std::string& sid() const {
    return _sid;
  }

private:
  std::string _sid;
}; // class Session

using session_ptr_t = std::shared_ptr<Session>;

class SessionManager {
public:
  static SessionManager& instance();

public:
  ~SessionManager();

  session_ptr_t new_session();

  session_ptr_t get_session(const std::string& sid);

private:
  SessionManager();
  SessionManager(const SessionManager&) = delete;
}; // class SessionManager

}; // namespace rina

#endif  //RINA_SESSION_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
