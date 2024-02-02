/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file agent.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 11:55:00
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_AGENT_H
#define RINA_AGENT_H

#include <string>
#include <map>

#include <spdlog/spdlog.h>

#include "memory.h"
#include "context.h"
#include "llm.h"

namespace rina {

class Agent {
public:
  Agent(const std::string& name)
    : _name(name) {}
  
  virtual ~Agent() {}

public:
  const std::string& name() const {
    return _name;
  }

  virtual int init(Memory* memory, LLM* llm, const std::string& persona) {
    spdlog::error("agent [{}] not implemented", this->name());
    return -1;
  }

  virtual int destroy() {
    spdlog::error("agent [{}] not implemented", this->name());
    return -1;
  }

  virtual message_ptr_t chat(context_ptr_t ctx, message_ptr_t msg) {
    spdlog::error("agent [{}] not implemented", this->name());
    return nullptr;
  }

  /*
  virtual Message* chat(const Message* msg) {
    spdlog::error("agent [{}] not implemented", this->name());
    return nullptr;
  }
  */

private:
  std::string _name;
}; // class Agent

class AgentManager {
public:
  static AgentManager* instance();

public:
  ~AgentManager() {}

  int init(const Configure& config);

  int destroy();

  int register_agent(const std::string& name, Agent* agent);

  Agent* get_agent(const std::string& name);

private:
  std::map<std::string, Agent*> _agents;
}; // class AgentManager

} // namespace rina

#endif  //RINA_AGENT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
