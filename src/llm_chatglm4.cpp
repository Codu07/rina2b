/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file llm_chatglm4.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 16:32:18
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "llm_chatglm4.h"

#include <chrono>
#include <ctime>

#include <jwt-cpp/jwt.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "http.h"

namespace rina {

using json = nlohmann::json;

static const std::string MODEL_URL = "https://open.bigmodel.cn/api/paas/v4/chat/completions";
static const std::string MODEL_ID = "glm-4";

static std::string generate_token(const std::string& apikey, int exp_time) {
  // parse id & secret from apikey
  auto split_pos = apikey.find(".");
  if (split_pos == std::string::npos) {
    spdlog::error("invalid apikey: {}", apikey);
    return "";
  }

  std::string id = apikey.substr(0, split_pos);
  std::string secret = apikey.substr(split_pos + 1);
  spdlog::info("{} : {}", id, secret);

  std::time_t ts_now = std::time(nullptr);
  std::time_t ts_exp_time = ts_now + exp_time;

  auto token = jwt::create()
    .set_header_claim("alg", jwt::claim(std::string("HS256")))
    .set_header_claim("sign_type", jwt::claim(std::string("SIGN")))
    .set_payload_claim("api_key", jwt::claim(id))
    .set_payload_claim("exp", picojson::value(int64_t{ts_exp_time}))
    .set_payload_claim("timestamp", picojson::value(int64_t{ts_now}))
    .sign(jwt::algorithm::hs256(secret));
  return token;
}

int ChatGLM4::init(const Configure& config) {
  return 0;
}
  
message_ptr_t ChatGLM4::chat(context_ptr_t ctx, message_ptr_t msg) {
  std::string prompt;
  int ret = build_prompt(ctx, msg, &prompt);
  if (ret != 0) {
    spdlog::error("build prompt failed: {}", ret);
    return nullptr;
  }

  auto token = generate_token(_api_key, 3600);
  if (token.empty()) {
    spdlog::error("generate token failed");
    return nullptr;
  }
  
  spdlog::info("token: {}", token);

  json req_data;
  req_data["model"] = "glm-4";
  req_data["messages"] = json::array();
  req_data["messages"].push_back(json::object({{"role", "user"}, {"content", prompt}}));

  std::string response;
  std::map<std::string, std::string> headers =
    {{"Content-Type", "application/json"}, {"Authorization", token}};
  std::map<std::string, std::string> params;
  std::string data = req_data.dump();
  ret = http_post(MODEL_URL, headers, params, data, &response);
  if (ret != 0) {
    spdlog::warn("http get failed: {}", ret);
    return nullptr;
  }

  auto response_msg = std::make_shared<ChatMessage>();

  spdlog::info("response: {}", response);

  return nullptr;
}

int ChatGLM4::build_prompt(context_ptr_t ctx, message_ptr_t msg, std::string* prompt) {
  json data;
  data["model"] = MODEL_ID;
  data["messages"] = json::array();
  data["messages"].push_back(json::object({{"role", "system"}, {"content", ctx->system_message()->get()}}));
  for (auto& msg : ctx->history()) {
    if (msg->type() == "chat") {
      //data["messages"].push_back(json::object({{"role", "user"}, {"content", msg->get()}}));
      continue;
    }
    if (msg->type() == "system") {
      continue;
    }
  }

  prompt->assign(data.dump());
  return 0;
}

int ChatGLM4::parse_response(const std::string& response, message_ptr_t msg) {
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
