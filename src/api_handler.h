/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_handler.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 18:04:05
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_API_HANDLER_H
#define RINA_API_HANDLER_H

#include <string>
#include <map>

namespace rina {

class APIHandler {
public:
  virtual ~APIHandler() {}

  virtual int handle(const std::string& method,
             const std::string& uri,
             const std::map<std::string, std::string>& params,
             const std::string& data,
             std::string* response) = 0;
}; // class APIHandler

} // namespace rina

#endif  //RINA_API_HANDLER_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
