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

namespace rina {

int ChatHandler::handle(const std::string& method,
                        const std::string& uri,
                        const std::map<std::string, std::string>& params,
                        const std::string& data,
                        std::string* response) {
  spdlog::info("Received chat request");
  return 0;
} // ChatHandler::handle

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
