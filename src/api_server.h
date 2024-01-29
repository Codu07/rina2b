/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_server.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 14:23:18
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_API_SERVER_H
#define RINA_API_SERVER_H

#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFServer.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFFacilities.h>

#include "configure.h"

namespace rina {

class APIServer {
public:
  APIServer() {}

  ~APIServer() {}

  int init(const Configure& config);

  int start();

  int wait_until_exit();

  int destroy();

public:
  static process(WFHttpTask* task);

private:
  WFHttpServer* _server {nullptr};
}; // class APIServer

} // namespace rina

#endif  //RINA_API_SERVER_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
