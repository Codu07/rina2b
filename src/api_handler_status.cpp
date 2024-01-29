/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_handler_status.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 18:16:18
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "api_handler_status.h"

#include <spdlog/spdlog.h>

namespace rina {

int StatusHandler::handle(const std::string& method,
                          const std::string& uri,
                          const std::map<std::string, std::string>& params,
                          const std::string& data,
                          std::string* response) {
  spdlog::info("Received status request");
  return 0;
} // StatusHandler::handle

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
