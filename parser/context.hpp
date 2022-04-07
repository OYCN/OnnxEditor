/**
 * @file context.hpp
 * @brief
 * @author oPluss (opluss@qq.com)
 *
 * @copyright Copyright (c) 2022  oPluss
 *
 * @par Modify log:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2022-04-07 <td>1.0     <td>oPluss     <td>Initial
 * </table>
 */

#ifndef PARSER_CONTEXT_HPP_
#define PARSER_CONTEXT_HPP_

#include <string>
#include <vector>

#include "onnx/onnx_pb.h"
#include "parser.hpp"
#include "utils.hpp"

#define LOG(msg, severity)                          \
  do {                                              \
    std::stringstream ss{};                         \
    if (severity >= LogLevel::kWARNING)             \
      ss << __FILE__ << ":" << __LINE__ << ": ";    \
    ss << msg;                                      \
    mCtx->mLogger->log(severity, ss.str().c_str()); \
  } while (0)

#define LOG_VERBOSE(msg) LOG(msg, LogLevel::kVERBOSE)
#define LOG_DEBUG(msg) LOG(msg, LogLevel::kDEBUG)
#define LOG_INFO(msg) LOG(msg, LogLevel::kINFO)
#define LOG_WARNING(msg) LOG(msg, LogLevel::kWARNING)
#define LOG_ERROR(msg) LOG(msg, LogLevel::kERROR)

namespace parser {

class Context {
 public:
  explicit Context(ILogger* log) : mLogger(log) {}
  ILogger* mLogger;
  ::ONNX_NAMESPACE::ModelProto mOnnxModel;
  std::string mFilePath;
  std::vector<size_t> mTopoOrder;
  std::vector<std::string> mInputs;
  std::vector<std::string> mOutputs;
  std::vector<std::string> mInitializers;
  std::vector<Node_t> mNodes;
};

}  // namespace parser

#endif  // PARSER_CONTEXT_HPP_
