/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file agent_lite.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/30 11:59:23
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_AGENT_LITE_H
#define RINA_AGENT_LITE_H

#include "agent.h"

namespace rina {

class LiteAgent : public Agent {
public:
  LiteAgent(const std::string& name) : Agent(name) {}

  virtual ~LiteAgent() {}

  virtual int init(Memory* memory, LLM* llm, const std::string& persona);

  virtual int destroy();

  virtual message_ptr_t chat(message_ptr_t msg);

private:
  std::string _persona {""};
  LLM* _llm {nullptr};
  Memory* _memory {nullptr};
}; // class LiteAgent

} // namespace rina

#endif  //RINA_AGENT_LITE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
