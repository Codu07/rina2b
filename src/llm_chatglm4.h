/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file llm_chatglm4.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 11:54:28
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_LLM_CHATGLM4_H
#define RINA_LLM_CHATGLM4_H

#include "llm.h"

namespace rina {

class ChatGLM4 : public LLM {
public:
  virtual ~ChatGLM4() {}

  virtual int init(const Configure& config);
  
  virtual message_ptr_t chat(context_ptr_t ctx, message_ptr_t msg);

  void set_api_key(const std::string& api_key) {
    _api_key = api_key;
  }

private:
  int build_prompt(message_ptr_t msg, std::string* prompt);

private:
  std::string _api_key;
  std::string _token;
  //int64_t _expire_time;
}; // class ChatGLM4

} // namespace rina

#endif  //RINA_LLM_CHATGLM4_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
