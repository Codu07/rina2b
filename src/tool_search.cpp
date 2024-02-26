/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file tool_search.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/07 17:40:32
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "tool_search.h"

namespace rina {

int SearchTool::init(const Configure& config) {
  return 0;
}

int SearchTool::destroy() {
  return 0;
}

int SearchTool::exec(nlohmann::json& data) {
  auto it = data.find("query");
  if (it->is_null()) {
    return -1;
  }
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
