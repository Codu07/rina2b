/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file agent.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 22:04:37
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "agent.h"
namespace {
::rina::AgentManager* g_ins = nullptr;
}

namespace rina {

AgentManager* AgentManager::instance() {
  if (g_ins == nullptr) {
    g_ins = new AgentManager();
  }

  return g_ins;
}

int AgentManager::init(const Configure& config) {
  return 0;
}

int AgentManager::destroy() {
  return 0;
}

int AgentManager::register_agent(const std::string& name, Agent* agent) {
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
