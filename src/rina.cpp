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

#include <fstream>

#include "llm.h"
#include "utils.h"

namespace rina {

int Rina::create(const Configure& config) {
  std::string llm_tag = config["llm"].as<std::string>();
  std::string memory_tag = config["memory"].as<std::string>();
  std::string persona_tag = config["persona"].as<std::string>();

  LLM* llm = LLMManager::instance()->get_llm(llm_tag);
  if (llm == nullptr) {
    spdlog::error("LLM {} not found", llm_tag);
    return -1;
  }

  Memory* memory = new Memory();

  Rina* rina = new Rina();
  if (rina->init(memory, llm, load_persona(persona_tag)) != 0) {
    spdlog::error("Failed to init Rina");
    delete rina;
    return -1;
  }

  return AgentManager::instance()->register_agent(rina->name(), rina);
}

int Rina::init(Memory* memory, LLM* llm, const std::string& persona) {
  _memory = memory;
  _llm = llm;
  _persona = persona;
  return 0;
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
