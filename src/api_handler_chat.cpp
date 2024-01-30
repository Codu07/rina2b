/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_handler_chat.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 18:16:11
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "api_handler_chat.h"

#include <spdlog/spdlog.h>

#include "agent.h"

namespace rina {

Message* build_message(const std::string& data) {
  return 0;
}

int ChatHandler::handle(const std::string& method,
                        const std::string& uri,
                        const std::map<std::string, std::string>& params,
                        const std::string& data,
                        std::string* response) {
  if (method.compare("POST") != 0) {
    spdlog::error("Unsupported method [{}]", method);
    return -1;
  }

  spdlog::info("Received chat request");
  AgentManager* am = AgentManager::instance();
  Agent* agent = am->get_agent("Rina2b");
  if (!agent) {
    spdlog::error("Failed to get agent [Rina2b]");
    return -1;
  }
  return 0;
} // ChatHandler::handle

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
