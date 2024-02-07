/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file knowledge_base.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/05 15:56:15
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_KNOWLEDGE_BASE_H
#define RINA_KNOWLEDGE_BASE_H

#include "knowledge.h"

namespace rina {

class KnowledgeBase {
public:
  static KnowledgeBase* instance();

public:
  ~KnowledgeBase() {}

  void insert(knowledge_ptr_t k);

private:
  KnowledgeBase() {};
  KnowledgeBase(const KnowledgeBase&) = delete;
}; // class KnowledgeBase

} // namespace rina

#endif  //RINA_KNOWLEDGE_BASE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
