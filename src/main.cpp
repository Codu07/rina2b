/***************************************************************************
 * 
 * Copyright (c) 2024 Wang Tao. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file main.cpp
 * @author wangtao(wtzhuque@163.com)
 * @date 2024/01/29 11:47:37
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <string>
#include <fstream>

#include <cxxopts.hpp>
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

#include "llm.h"
#include "api_server.h"

namespace rina {

int run(int argc, char** argv) {
  // parse args with cxxopt
  cxxopts::Options option_parser("rina", "RINA API Server");
  option_parser.add_options()
    ("p,port", "port number", cxxopts::value<int>()->default_value("8087"))
    ("c,config", "config file", cxxopts::value<std::string>()->default_value("./config/rina.yaml"))
    ("h,help", "Print usage");
  auto options = option_parser.parse(argc, argv);

  std::ifstream ifs(options["config"].as<std::string>());
  YAML::Node config = YAML::Load(ifs);

  auto llm_config = config["llm"];
  LLMManager* llms = LLMManager::instance();
  int ret = llms->init(llm_config);
  if (ret != 0) {
    spdlog::error("failed to init llm");
    return ret;
  }
  spdlog::info("init llms success");

  auto rina_config = config["rina"];

  auto api_server_config = config["server"];
  
  APIServer* server = APIServer::instance();
  ret = server->init(api_server_config);
  if (ret != 0) {
    spdlog::error("failed to init api server");
    return ret;
  }

  ret = server->start(options["port"].as<int>());
  if (ret != 0) {
    spdlog::error("failed to start api server");
    return ret;
  }
  spdlog::info("start api server on {}", options["port"].as<int>());
  
  ret = server->wait_until_exit();
  if (ret != 0) {
    spdlog::warn("failed to wait server exit");
  }

  ret = server->destroy();
  if (ret != 0) {
    spdlog::warn("failed to destroy server");
  }

  spdlog::info("api server exit");
  return 0;
} // int run()

} // namespace rina

int main(int argc, char** argv) {
  return ::rina::run(argc, argv);
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
