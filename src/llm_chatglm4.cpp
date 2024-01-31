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

namespace rina {

static const std::string url = "http://127.0.0.1:8080/chat";

static std::string generate_token(const std::string& apikey, int exp_time) {
  // parse id & secret from apikey
  auto split_pos = apikey.find(".");
  if (split_pos == std::string::npos) {
    spdlog::error("invalid apikey: {}", apikey);
    return "";
  }

  std::string id = apikey.substr(0, split_pos);
  std::string secret = apikey.substr(split_pos + 1);
  spdlog::info("{} : {}", id, secret)

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
  int ret = build_prompt(msg, &prompt);
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
  return nullptr;
}

int ChatGLM4::build_prompt(message_ptr_t msg, std::string* prompt) {
  // TODO: build prompt
  prompt->assign("hello");
  return 0;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
