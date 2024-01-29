/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file llm.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 15:11:49
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "llm.h"

#include <spdlog/spdlog.h>

#include "llm_chatglm4.h"

namespace {
static ::rina::LLMManager* g_ins = nullptr;
}

const std::string LLM_TYPE_CHATGLM3 = "chatglm3";
const std::string LLM_TYPE_CHATGLM4 = "chatglm4";

namespace rina {

LLMManager& LLMManager::get_instance() {
  if (g_ins == nullptr) {
    g_ins = new LLMManager();
  }

  return *g_ins;
}

int LLMManager::init(const Configure& config) {
  for (const auto& item : config) {
    std::string name = item["name"].as<std::string>();
    std::string type = item["type"].as<std::string>();

    spdlog::info(fmt::format("name: {}, type: {}", name, type));

    if (type.compare(LLM_TYPE_CHATGLM4) == 0) {
      ChatGLM4* chatglm4 = new ChatGLM4();
      chatglm4->init(item);
      _llms[name] = chatglm4;
      continue;
    }

    spdlog::warn(fmt::format("unknown llm type: {}", type));
  }
 
  return 0;
}

int LLMManager::destroy() {
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
