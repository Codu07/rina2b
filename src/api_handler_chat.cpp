/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file api_handler_chat.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 18:16:11
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "api_handler_chat.h"

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "agent.h"
#include "session.h"

namespace rina {

using json = nlohmann::json;

static const std::string ROLE_USER = "user";
static const std::string ROLE_AGENT = "agent";

Message* build_message(const std::string& data) {
  return 0;
}

int ChatHandler::handle(const std::string& method,
                        const std::string& uri,
                        const std::map<std::string, std::string>& params,
                        const std::string& data,
                        std::string* response) {
  if (method.compare("POST") != 0) {
    spdlog::error("unsupported method [{}]", method);
    return -1;
  }

  std::string sid;
  std::string message;

  try { 
    json node = json::parse(data);
    if (node.is_null()) {
      spdlog::error("failed to parse json data [{}]", data);
      return -1;
    }
    sid = node["sid"];
    message = node["message"];
  } catch (const json::exception& e) {
    spdlog::error("failed to parse json data [{}], error [{}]", data, e.what());
    return -1;
  }

  SessionManager* sm = SessionManager::instance();
  session_ptr_t session = sm->get_session(sid);
  if (!session) {
    session = sm->new_session();
    spdlog::info("new session [{}] created", session->sid());
  }

  if (!session->ctx()) {
    spdlog::error("session [{}] has no context", session->sid());
    return -1;
  }

  auto chat_message = std::make_shared<ChatMessage>(ROLE_USER, message);

  spdlog::info("Received chat request:\n{}", data);
  AgentManager* am = AgentManager::instance();
  Agent* agent = am->get_agent("Rina2b");
  if (!agent) {
    spdlog::error("Failed to get agent [Rina2b]");
    return -1;
  }

  auto response_message = agent->chat(session->ctx(), chat_message);
  if (!response_message) {
    spdlog::error("Failed to chat with agent [Rina2b]");
    return -1;
  }

  if (response_message->type() == "chat") {
    auto chat_response = std::static_pointer_cast<ChatMessage>(response_message);

    json response_data;
    response_data["sid"] = session->sid();
    response_data["role"] = ROLE_AGENT;
    response_data["message"] = chat_response->content();
    response->assign(response_data.dump());
  } else {
    spdlog::error("unexpected response message type [{}]", response_message->type());
    return -1;
  }

  return 0;
} // ChatHandler::handle

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
