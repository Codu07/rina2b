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

#include <map>
#include <string>
#include <memory>

#include <nlohmann/json.hpp>

namespace rina {

class Tool {
public:
  Tool() {}

  virtual ~Tool() {}

  virtual int init(const Configure& /*config*/) {
    return 0;
  }

  virtual int destroy() {
    return 0;
  }

  virtual int exec(nlohmann::json& data) = 0;
}; // class Tool

using tool_ptr_t = std::shared_ptr<Tool>;

} // namespace rina

#endif  //RINA_TOOL_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
