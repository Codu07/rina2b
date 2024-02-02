/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file deep_think_pipeline.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/02 17:52:45
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_DEEP_THINK_PIPELINE_H
#define RINA_DEEP_THINK_PIPELINE_H

#include <queue>
#include <mutex>

#include "message.h"

namespace rina {

class MessagePipe;

class DeepThinkPipeline {
public:
  DeepThinkPipeline();

  ~DeepThinkPipeline();

public:
  int init();

  int destroy();

  int append_message(message_ptr_t msg);

private:
  MessagePipe* _pipe {nullptr};
}; // class DeepThinkPipeline

class MessagePipe {
public:
  MessagePipe();

  ~MessagePipe();

public:
  void push(message_ptr_t msg);

  message_ptr_t pop();

private:
  std::queue<message_ptr_t> _queue;
  std::mutex _mutex; 
}; // class MessagePipe

} // namespace rina

#endif  //RINA_DEEP_THINK_PIPELINE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
