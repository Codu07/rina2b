/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file tool.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/30 11:28:28
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_TOOL_H
#define RINA_TOOL_H

#include "configure.h"

namespace rina {

class Tool {
public:
  Tool();

  ~Tool();
}; // class Tool

class ToolManager {
public:
  static ToolManager* getInstance();

  ~ToolManager();

  int init(const Configure& config);

private:
  ToolManager() {}
  ToolManager(const ToolManager&) {}
}; // class ToolManager

} // namespace rina

#endif  //RINA_TOOL_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
