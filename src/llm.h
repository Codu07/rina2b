/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file llm.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 11:53:45
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_LLM_H
#define RINA_LLM_H

#include <string>

#include "configure.h"
#include "message.h"

namespace rina {

class LLM {
public:
  virtual ~LLM() {}

  virtual int init(const Configure& config) {
    return 0;
  }

  virtual Message* chat(const Message* msg) = 0;
}; // class LLM

class LLMManager {
public:
  static LLMManager* instance();

public:
  ~LLMManager() {}

  int init(const Configure& config);

  int destroy();

  bool register_llm(const std::string& name, LLM* llm);

  LLM* get_llm(const std::string& name);

private:
  LLMManager() {}
  LLMManager(const LLMManager&) {}

private:
  std::map<std::string, LLM*> _llms;
}; // class LLMManager

} // namespace rina

#endif  //RINA_LLM_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
