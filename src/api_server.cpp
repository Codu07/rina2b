/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_server.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 14:23:24
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "api_server.h"

#include <spdlog/spdlog.h>

#include "api_handler_chat.h"
#include "api_handler_status.h"

namespace {
static ::rina::APIServer* g_ins = nullptr;
}

static WFFacilities::WaitGroup wait_group(1);
void sig_handler(int sig) {
  wait_group.done();
}

namespace rina {

static const std::string API_CHAT = "/api/chat";
static const std::string API_STATUS = "/api/status";

APIServer* APIServer::instance() {
  if (g_ins == nullptr) {
    g_ins = new APIServer();
  }

  return g_ins;
}

void APIServer::process(WFHttpTask* task) {
  auto request = task->get_req();
  auto response = task->get_resp();

  // parse request
  std::string method = request->get_method();
  std::string uri = request->get_request_uri();
  std::map<std::string, std::string> params;
  std::string data;

  if (method == "POST") { 
    // parse body  
    const void* body;
    size_t body_len;
    request->get_parsed_body(&body, &body_len);
    if (body_len > 0) {
      data = std::string(static_cast<const char*>(body), body_len);
    }
  }

  std::string response_data;

  APIServer* api_server = APIServer::instance();
  api_server->handle(method, uri, params, data, &response_data);

  response->append_output_body(response_data);
  response->set_http_version("HTTP/1.1");
  response->set_status_code("200");
  response->set_reason_phrase("OK");
}

int APIServer::init(const Configure& config) {
  if (_server != nullptr) {
    return 0;
  }

  _server = new WFHttpServer(APIServer::process);

  _handlers[API_CHAT] = new ChatHandler();
  _handlers[API_STATUS] = new StatusHandler();
	return 0;
}

int APIServer::destroy() {
  delete _server;
  _server = nullptr;

  for (auto& it : _handlers) {
    delete it.second;
    it.second = nullptr;
  }
  _handlers.clear();
  return 0;
}

int APIServer::start(int port) {
  int ret = _server->start(port);
  if (ret != 0) {
    spdlog::error("Failed to start API server {}", ret);
    return ret;
  }
  return 0;
}

int APIServer::wait_until_exit() {
  wait_group.wait();
  _server->stop();
  return 0;
}

int APIServer::handle(const std::string& method,
               const std::string& uri,
               const std::map<std::string, std::string>& params,
               const std::string& data,
               std::string* response) {
  auto it = _handlers.find(uri);
  if (it == _handlers.end()) {
    spdlog::error("Unknown API: {}", uri);
    return -1;
  }

  APIHandler* handler = it->second;
  return handler->handle(method, uri, params, data, response);
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
