/**
 * Copyright (c) 2016 by Contributors
 */
#ifndef PS_ENV_H_
#define PS_ENV_H_
#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <memory>
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
  static std::shared_ptr<Environment> Init(std::unordered_map<const char*, const char*>* envs) {
    return Get(envs);
  }

  const char* find(const char* k) {
    return kvs.find(k) == kvs.end() ? getenv(k) : kvs[k];
  }
  ~Environment() { std::cout << "Env destruction " << getenv("DMLC_ROLE") << std::endl; }

 private:
  explicit Environment(std::unordered_map<const char*, const char*>* envs) {
    if (envs) kvs = *envs;
  }

  static std::shared_ptr<Environment> Get(std::unordered_map<const char*, const char*>* envs) {
    static std::shared_ptr<Environment> inst_ptr(new Environment(envs));
    return inst_ptr;
  }

  std::unordered_map<const char*, const char*> kvs;
};

}  // namespace ps
#endif  // PS_ENV_H_
