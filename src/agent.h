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

#include "memory.h"
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

  virtual int init(Memory* memory, LLM* llm, const std::string& persona);

  virtual int destroy();

  virtual Message* chat(const Message* msg);

private:
  std::string _name;
}; // class Agent

class AgentManager {
public:
  AgentManager* instance();

public:
  ~AgentManager() {}

  int init(const Configure& config);

  int destroy();

  int register_agent(const std::string& name, Agent* agent);
}; // class AgentManager

} // namespace rina

#endif  //RINA_AGENT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
