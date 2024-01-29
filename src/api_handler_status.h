/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_handler_status.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 18:12:28
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_API_HANDLER_STATUS_H
#define RINA_API_HANDLER_STATUS_H

#include "api_handler.h"

namespace rina {

class StatusHandler : public APIHandler {
public:
  virtual ~StatusHandler() {}

  virtual int handle(const std::string& method,
             const std::string& uri,
             const std::map<std::string, std::string>& params,
             const std::string& data,
             std::string* response);
}; // class StatusHandler

} // namespace rina

#endif  //RINA_API_HANDLER_STATUS_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
