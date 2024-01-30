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

#include <fstream>
#include <spdlog/spdlog.h>

#include "llm.h"
#include "memory.h"

#include "agent_lite.h"

namespace {
static ::rina::AgentManager* g_ins = nullptr;
}

namespace rina {

static const std::string AGENT_PERSONA_PATH = "./config/persona";
std::string load_persona(const std::string& tag) {
  std::string path = AGENT_PERSONA_PATH + "/" + tag + ".txt";
  // Load file from path

  std::ifstream f(path);
  if (!f.is_open()) {
    spdlog::error("Failed to load persona file {}", path);
  }

  std::stringstream ss;
  ss << f.rdbuf();
  return ss.str();
}

AgentManager* AgentManager::instance() {
  if (g_ins == nullptr) {
    g_ins = new AgentManager();
  }

  return g_ins;
}

int AgentManager::init(const Configure& config) {
  LLMManager* llms = LLMManager::instance();

  for (const auto& item : config) {
    std::string name = item["name"].as<std::string>();
    std::string llm_tag = item["llm"].as<std::string>();
    std::string memory_tag = item["memory"].as<std::string>();
    std::string persona_tag = item["persona"].as<std::string>();

    // Look for llm
    LLM* llm = llms->get_llm(llm_tag);
    if (llm == nullptr) {
      spdlog::error("agent [{}] llm: {} not found", name, llm_tag);
      continue;
    }

    // TODO: load memory
    Memory* memory = new Memory();

    // Load Memory
    std::string persona = load_persona(persona_tag);

    // Load Tools
    auto tools = item["tools"];
    for (const auto& tool_item : tools) {
      std::string tool_name = tool_item.as<std::string>();
      spdlog::info("agent name: {} register tool: {}", name, tool_name);
    }

    // Build Agent
    Agent* agent = new LiteAgent(name);
    if (agent->init(memory, llm, persona) != 0) {
      spdlog::error("agent name: {} init failed", name);
      continue;
    }

    // register agent
    if (this->register_agent(name, agent) != 0) {
      spdlog::error("agent name: {} register failed", name);
      continue;
    } 
    spdlog::info("agent name: {} init success", name);
  }
 
  return 0;
}

int AgentManager::destroy() {
  for (auto it : _agents) {
    delete it.second;
  }

  _agents.clear();
  return 0;
}

int AgentManager::register_agent(const std::string& name, Agent* agent) {
  auto it = _agents.find(name);
  if (it != _agents.end()) {
    spdlog::error("agent name [{}] already exists", name);
    return -1;
  }

  _agents.insert(std::make_pair(name, agent));
  return 0;
}

Agent* AgentManager::get_agent(const std::string& name) {
  auto it = _agents.find(name);
  if (it == _agents.end()) {
    spdlog::warn("agent name [{}] not found", name);
    return nullptr;
  }

  return it->second;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
