/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file http.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/31 16:32:47
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "http.h"

#include <spdlog/spdlog.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>

namespace rina {

static const int HTTP_REDIRECT_MAX = 5;
static const int HTTP_RETRY_MAX = 3;

static const std::string HTTP_METHOD_GET = "GET";
static const std::string HTTP_METHOD_POST = "POST";

struct TaskContext {
  int error_code {0};
  std::string error_msg;
  std::string response;
  WFFacilities::WaitGroup wait_group{1};
}; // struct TaskContext

int http_get(const std::string& url,
             const std::map<std::string, std::string>& headers,
             const std::map<std::string, std::string>& params,
             std::string* response) {
  WFHttpTask* task = WFTaskFactory::create_http_task(url, HTTP_REDIRECT_MAX, HTTP_RETRY_MAX, nullptr);
  auto req = task->get_req();
  for (auto& it : headers) {
    req->add_header_pair(it.first, it.second);
  }

  req->set_method(HTTP_METHOD_GET);

  TaskContext* ctx = new TaskContext();
  task->set_callback([ctx](WFHttpTask* task) {
    int state = task->get_state();
    int error = task->get_error();

    spdlog::info("http request state: {}, error: {}", state, error);

    switch (state) {
      case WFT_STATE_SYS_ERROR:
        spdlog::warn("http system error: {}", state);
        break;
      case WFT_STATE_DNS_ERROR:
        spdlog::warn("http dns error: {}", state);
        break;
      case WFT_STATE_SSL_ERROR:
        spdlog::warn("http ssl error: {}", state);
        break;
    }

    if (state != WFT_STATE_SUCCESS) {
      spdlog::warn("http request failed");
      ctx->error_code = state;
      ctx->error_msg = task->get_error();
      ctx->wait_group.done();
      return;
    }
    
    ctx->wait_group.done();
  });
  
  task->start();
  ctx->wait_group.wait();
  delete ctx;
  return 0;
}

int http_post(const std::string& url,
              const std::map<std::string, std::string>& headers,
              const std::map<std::string, std::string>& params,
              const std::string& body,
              std::string* response) {
  WFHttpTask* task = WFTaskFactory::create_http_task(url, HTTP_REDIRECT_MAX, HTTP_RETRY_MAX, nullptr);
  auto req = task->get_req();
  for (auto& it : headers) {
    req->add_header_pair(it.first, it.second);
  }

  req->set_method(HTTP_METHOD_POST);
  req->append_output_body(body.c_str(), body.size());

  TaskContext* ctx = new TaskContext();
  task->set_callback([ctx](WFHttpTask* task) {
    int state = task->get_state();
    int error = task->get_error();

    spdlog::info("http request state: {}, error: {}", state, error);

    switch (state) {
      case WFT_STATE_SYS_ERROR:
        spdlog::warn("http system error: {}", state);
        break;
      case WFT_STATE_DNS_ERROR:
        spdlog::warn("http dns error: {}", state);
        break;
      case WFT_STATE_SSL_ERROR:
        spdlog::warn("http ssl error: {}", state);
        break;
    }

    if (state != WFT_STATE_SUCCESS) {
      ctx->error_code = state;
      ctx->error_msg = task->get_error();
      ctx->wait_group.done();
      return;
    }
    
    protocol::HttpChunkCursor cursor(task->get_resp());
    const void* chunk;
    size_t size;
    std::string body;
    while (cursor.next(&chunk, &size)) {
	    std::string chunk_body = std::string((const char*)chunk, size);
	    body += chunk_body;
    }

    ctx->response.swap(body);
    ctx->wait_group.done();
  });
  
  task->start();
  ctx->wait_group.wait();
  response->swap(ctx->response);
  delete ctx;
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
