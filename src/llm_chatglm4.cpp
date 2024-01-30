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

#include <jwt-cpp/jwt.h>

namespace rina {

static const std::string url = "http://127.0.0.1:8080/chat";

static std::string generate_token(const std::string& apikey, int exp_time) {
  // Generate timestamp

  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  auto token = jwt::create()
    .set_header_claim("alg", jwt::claim(std::string("HS256")))
    .set_header_claim("sign_type", jwt::claim(std::string("SIGN")))
    .set_payload_claim("api_key", jwt::claim(apikey))
    .set_payload_claim("exp", picojson::value(int64_t{exp_time}))
    .set_payload_claim("timestamp", picojson::value(int64_t{ts.count()}))
    .sign(jwt::algorithm::hs256(apikey));
  return token;
}

static int build_prompt() {
  return 0;
}

int ChatGLM4::init(const Configure& config) {
  return 0;
}
  
message_ptr_t ChatGLM4::chat(context_ptr_t ctx, message_ptr_t msg) {
  return nullptr;
}

} // namespace rina

/* vim: set ts=4 sw=4 sts=4 tw=100 */
