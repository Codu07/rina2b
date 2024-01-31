/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file http.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/31 16:32:47
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "http.h"

namespace rina {

int http_get(const std::string& url,
             const std::string& headers,
             const std::map<std::string, std::string>& params,
             std::string* response) {  
  return 0;
}

int http_post(const std::string& url,
              const std::string& headers,
              const std::map<std::string, std::string>& params,
              const std::string& body,
              std::string& response) {
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
