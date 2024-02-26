/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file tool_manager.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/07 17:55:46
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "tool_manager.h"

#include <spdlog/spdlog.h>

#include "tool_search.h"

namespace {
::rina::ToolManager* g_ins = nullptr;
} // namesapce

namespace rina {

ToolManager* ToolManager::instance() {
  if (g_ins == nullptr) {
    g_ins = new ToolManager();
  }
  return g_ins;
} // get_instance

int ToolManager::init(const Configure& conf) {
  // init search tool
  tool_ptr_t search_tool = std::make_shared<SearchTool>();
  if (this->register_tool("search", search_tool) != 0) {
    spdlog::error("register search tool failed");
    return -1;
  }

  return 0;
} // init

int ToolManager::destroy() {
  for (auto& item : _tools) {
    item.second->destroy();
    item.second = nullptr;
  }

  _tools.clear();
  return 0;
}

int ToolManager::register_tool(const std::string& tool_name, tool_ptr_t tool) {
  auto it = _tools.find(tool_name);
  if (it!= _tools.end()) {
    spdlog::warn("tool {} already registered", tool_name);
    return -1;
  }

  _tools[tool_name] = tool;
  return 0;
}

int ToolManager::invoke(const std::string& tool_name, ::nlohmann::json& data) {
  auto it = _tools.find(tool_name);
  if (it == _tools.end()) {
    spdlog::warn("tool {} not found", tool_name);    
    return -1;
  }

  auto tool = it->second;
  return tool->exec(data);
}
} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
