/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file utils.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/30 16:47:27
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "utils.h"

#include <fstream>
#include <sstream>

#include <spdlog/spdlog.h>

namespace rina {

static const std::string AGENT_PERSONA_PATH = "./config/persona";
std::string load_persona(const std::string& tag) {
  std::string path = AGENT_PERSONA_PATH + "/" + tag + ".txt";

  std::ifstream f(path);
  if (!f.is_open()) {
    spdlog::error("Failed to load persona file {}", path);
  }

  std::stringstream ss;
  ss << f.rdbuf();
  return ss.str();
} // load_persona

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
