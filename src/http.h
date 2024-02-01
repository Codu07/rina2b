/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file http.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/31 16:28:51
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_HTTP_H
#define RINA_HTTP_H

#include <string>
#include <map>

namespace rina {

int http_get(const std::string& url,
             const std::map<std::string, std::string>& headers,
             const std::map<std::string, std::string>& params,
             std::string* response);

int http_post(const std::string& url,
             const std::map<std::string, std::string>& headers,
              const std::map<std::string, std::string>& params,
              const std::string& body,
              std::string* response);

} // namespace rina

#endif  //RINA_HTTP_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
