/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file memory.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 11:54:53
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_MEMORY_H
#define RINA_MEMORY_H

#include "message.h"
#include "knowledge.h"

namespace rina {

class ShortMemory;
class LongMemory;

class Memory {
public:
  Memory() {}

  ~Memory() {}

  int seek_latest_message();

  int append_message(Message* msg);

  int seek_related_knowledge();

  int append_knowledge(Knowledge* knowledge);

private:
  ShortMemory* _short_memory {nullptr};
  LongMemory* _long_memory {nullptr};
}; // class Memory

class ShortMemory {
public:
  ShortMemory() {}

  ~ShortMemory() {}
}; // class ShortMemory

class LongMemory {
public:
  LongMemory() {}

  ~LongMemory() {}
}; // class LongMemory

} // namespace rina

#endif  //RINA_MEMORY_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
