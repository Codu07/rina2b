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

#include <sstream>

#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>

namespace rina {

using json = nlohmann::json;

static const int HTTP_REDIRECT_MAX = 5;
static const int HTTP_RETRY_MAX = 3;
static const int RECV_TIMEOUT = 120000;
//static const int CONNECT_TIMEOUT = 10000;

static const std::string HTTP_METHOD_GET = "GET";
static const std::string HTTP_METHOD_POST = "POST";

static const std::string HTTP_CHUNK_PREFIX = "data: ";

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

    spdlog::info("http request state: {}", state);

    switch (state) {
      case WFT_STATE_SYS_ERROR:
        spdlog::warn("http system error: {}", strerror(error));
        break;
      case WFT_STATE_DNS_ERROR:
        spdlog::warn("http dns error: {}", gai_strerror(error));
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
    std::stringstream ss;
    const void* chunk;
    size_t size;
    std::string body;
    while (cursor.next(&chunk, &size)) {
      std::string chunk_body = std::string((const char*)chunk, size);
      ss << chunk_body;
      spdlog::info("raw body: {}", chunk_body);

      //if (!chunk_body.starts_with(HTTP_CHUNK_PREFIX)) {
      //  continue;
      //}

      //std::string chunk_body_without_prefix = chunk_body.substr(HTTP_CHUNK_PREFIX.size());
      //if (chunk_body_without_prefix.compare("[DONE]") == 0) {
      //  break;
      //}

      //spdlog::info("chunk body: {}", chunk_body_without_prefix);

      //json j = json::parse(chunk_body_without_prefix);
      //body += j["choices"][0]["delta"]["content"];
	    //body += chunk_body;
    }

    std::string chunk_buf;
    json resp_json;
    while (getline(ss, chunk_buf)) {
      if (chunk_buf.empty()) {
        continue;
      }
      if (!chunk_buf.starts_with(HTTP_CHUNK_PREFIX)) {
        continue;
      }
      
      std::string chunk_body_without_prefix = chunk_buf.substr(HTTP_CHUNK_PREFIX.size());
      if (chunk_body_without_prefix.compare("[DONE]") == 0) {
        break;
      }

      resp_json.push_back(json::parse(chunk_body_without_prefix));
    }

    spdlog::info("response body: {}", resp_json.dump());

    ctx->response = resp_json.dump();
    ctx->wait_group.done();
  });

  task->set_receive_timeout(RECV_TIMEOUT);
  //task->set_send_timeout();
  task->set_wait_timeout(RECV_TIMEOUT);
  //task->set_watch_timeout();

  task->start();
  ctx->wait_group.wait();
  response->swap(ctx->response);
  delete ctx;
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
