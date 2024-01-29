/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_handler_chat.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 18:12:17
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_API_HANDLER_CHAT_H
#define RINA_API_HANDLER_CHAT_H

#include "api_handler.h"

namespace rina {

class ChatHandler : public APIHandler {
public:
  virtual ~ChatHandler() {}

  virtual int handle(const std::string& method,
             const std::string& uri,
             const std::map<std::string, std::string>& params,
             const std::string& data,
             std::string* response);
}; // class ChatHandler

} // namespace rina

#endif  //RINA_API_HANDLER_CHAT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
