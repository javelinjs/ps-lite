/**
 * Copyright (c) 2016 by Contributors
 */
#ifndef PS_ENV_H_
#define PS_ENV_H_
#include <cstdlib>
#include <unordered_map>
namespace ps {

/**
 * \brief Environment configurations
 */
class Environment {
 public:
  /**
   * \brief return the singleton object
   */
  static Environment* Get() {
    return Get(nullptr);
  }
  static Environment* Init(std::unordered_map<const char*, const char*>* envs) {
    return Get(envs);
  }

  const char* find(const char* k) {
    return kvs.find(k) == kvs.end() ? getenv(k) : kvs[k];
  }

 private:
  explicit Environment(std::unordered_map<const char*, const char*>* envs) {
    if (envs) kvs = *envs;
  }

  static Environment* Get(std::unordered_map<const char*, const char*>* envs) {
    static Environment e(envs);
    return &e;
  }

  std::unordered_map<const char*, const char*> kvs;
};

}  // namespace ps
#endif  // PS_ENV_H_
