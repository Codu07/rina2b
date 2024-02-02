/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file rina.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 12:07:56
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_RINA_H
#define RINA_RINA_H

#include "agent.h"
#include "configure.h"

namespace rina {

class Rina : public Agent {
public:
  static int create(const Configure& config);

public:
  Rina() : Agent("Rina2b") {}

  virtual ~Rina() {}

  virtual int init(Memory* memory, LLM* llm, const std::string& persona);

  virtual int destroy();

  virtual message_ptr_t chat(context_ptr_t ctx, message_ptr_t msg);

private:
  Memory* _memory {nullptr};
  LLM* _llm {nullptr};
  std::string _persona {""};
}; // class Rina

} // namespace rina

#endif  //RINA_RINA_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
