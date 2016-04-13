/**
 * Copyright (c) 2016 by Contributors
 */
#ifndef PS_ENV_H_
#define PS_ENV_H_
#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>
namespace ps {

/**
 * \brief Environment configurations
 */
class Environment {
 public:
  /**
   * \brief return the singleton object
   */
  static std::shared_ptr<Environment> Get() {
    return Get(nullptr);
  }
  static std::shared_ptr<Environment> Init(std::unordered_map<std::string, std::string>& envs) {
    return Get(&envs);
  }

  const char* find(const char* k) {
  	std::cout << "KV size: " << kvs.size() << std::endl;
	for (auto i : kvs) {
	  std::cout << i.first << " " << i.second << std::endl;
	}
	std::string key(k);
	std::cout << "num_worker: " << kvs["DMLC_NUM_WORKER"] << std::endl;
	std::cout << "num_worker: " << kvs[key] << std::endl;
    return kvs.find(key) == kvs.end() ? getenv(k) : kvs[key].c_str();
  }
  ~Environment() { std::cout << "Env destruction " << find("DMLC_ROLE") << std::endl; }

 private:
  explicit Environment(std::unordered_map<std::string, std::string>* envs) {
    if (envs) kvs = *envs;
  }

  static std::shared_ptr<Environment> Get(std::unordered_map<std::string, std::string>* envs) {
  	if (envs) std::cout << "Env input: " << envs->size() << std::endl;
    static std::shared_ptr<Environment> inst_ptr(new Environment(envs));
    return inst_ptr;
  }

  std::unordered_map<std::string, std::string> kvs;
};

}  // namespace ps
#endif  // PS_ENV_H_
