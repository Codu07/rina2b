/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file knowledge.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/30 15:50:47
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_KNOWLEDGE_H
#define RINA_KNOWLEDGE_H

#include <string>

namespace rina {

class Knowledge {
public:
  Knowledge() {}

  Knowledge(const std::string& question,
            const std::string& answer)
    : _question(question), _answer(answer) {}

  ~Knowledge() {}

  const std::string& question() const {
    return _question;
  }

  const std::string& answer() const {
    return _answer;
  }

  void set(const std::string& question,
           const std::string& answer) {
    _question = question;
    _answer = answer; 
  }

private:
  std::string _question;
  std::string _answer;
}; // class Knowledge

} // namespace rina

#endif  //RINA_KNOWLEDGE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
