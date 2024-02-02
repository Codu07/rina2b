/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file session.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/01 22:13:32
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "session.h"

namespace {
static ::rina::SessionManager* g_ins = nullptr;
} // namespace

namespace rina {

static std::string generate_session_id() {
  //TODO: generate session id
  return "12345678";
}

SessionManager* SessionManager::instance() {
  if (g_ins == nullptr) {
    g_ins = new SessionManager();
  }
  return g_ins;
}

int SessionManager::init() {
  return 0;
}

int SessionManager::destroy() {
  return 0;
}

session_ptr_t SessionManager::new_session() {
  session_ptr_t session = std::make_shared<Session>(generate_session_id());
  _sessions[session->sid()] = session;
  return session;
}

session_ptr_t SessionManager::get_session(const std::string& sid) {
  auto it = _sessions.find(sid);
  if (it == _sessions.end()) {
    return nullptr;
  }
  return it->second;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
