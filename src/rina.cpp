/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file rina.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 12:17:30
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "rina.h"

namespace rina {

int Rina::init(Memory* memory, LLM* llm, const std::string& persona) {
  _memory = memory;
  _llm = llm;
  _persona = persona;

  return AgentManager::instance()->register_agent(this->name(), this);
}

int Rina::destroy() {
  _memory = 0;
  _llm = 0;
  _persona = "";
  return 0;
}

Message* Rina::chat(const Message* msg) {
  return nullptr;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
