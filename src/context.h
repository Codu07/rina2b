/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file context.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 14:17:21
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_CONTEXT_H
#define RINA_CONTEXT_H

#include <memory>
#include <string>

#include "message.h"

namespace rina {

class Context {
public:
  Context() {}

  ~Context() {}

private:
  system_message_ptr_t _system_message;
  std::vector<message_ptr_t> _history; 
}; // class Context

using context_ptr_t = std::shared_ptr<Context>;

} // namespace rina

#endif  //RINA_CONTEXT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
