/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file tool_search.h
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/02/07 17:17:21
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef RINA_TOOL_SEARCH_H
#define RINA_TOOL_SEARCH_H

#include "tool.h"

namespace rina {

class SearchTool : public Tool {
public:
  SearchTool() {}

  virtual ~SearchTool() {}

  virtual int init(const Configure& config);

  virtual int destroy();

  virtual int exec(nlohmann::json& data);
}; // class SearchTool

} // namespace rina

#endif  //RINA_TOOL_SEARCH_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
