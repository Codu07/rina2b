/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file agent_lite.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/30 12:03:10
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "agent_lite.h"

#include <spdlog/spdlog.h>

namespace rina {

int LiteAgent::init(Memory* memory, LLM* llm, const std::string& persona) {
  _llm = llm;
  _memory = memory;
  _persona = persona;
  return 0;
}

int LiteAgent::destroy() {
  _llm = nullptr;
  _memory = nullptr;
  _persona = "";
  return 0;
}

Message* LiteAgent::chat(const Message* msg) {
  if (_llm == nullptr || _memory == nullptr) {
    spdlog::error("agent [{}] not initialized", this->name());
    return nullptr;
  }

  return nullptr;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
