/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file tool_manager.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/07 17:55:38
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_TOOL_MANAGER_H
#define RINA_TOOL_MANAGER_H

#include <map>
#include <string>
#include <nlohmann/json.hpp>

#include "configure.h"
#include "tool.h"

namespace rina {

class ToolManager {
public:
  static ToolManager* instance();

  ~ToolManager();

  int init(const Configure& config);

  int destroy();

  int register_tool(const std::string& tool_name, tool_ptr_t tool);

  int invoke(const std::string& tool_name, nlohmann::json& data);

private:
  ToolManager() {}
  ToolManager(const ToolManager&) {}

private:
  std::map<std::string, tool_ptr_t> _tools;
}; // class ToolManager

} // namespace rina

#endif  //RINA_TOOL_MANAGER_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
