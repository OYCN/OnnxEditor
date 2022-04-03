#ifndef CONTEXT_H
#define CONTEXT_H

#include "onnx/onnx_pb.h"

#include "parser.h"
#include "utils.h"

#define LOG(msg, severity)                                                             \
    do {                                                                               \
        std::stringstream ss{};                                                        \
        if (severity >= LogLevel::kWARNING) ss << __FILE__ << ":" << __LINE__ << ": "; \
        ss << msg;                                                                     \
        mCtx->mLogger->log(severity, ss.str().c_str());                                \
    } while (0)

#define LOG_VERBOSE(msg) LOG(msg, LogLevel::kVERBOSE)
#define LOG_DEBUG(msg) LOG(msg, LogLevel::kDEBUG)
#define LOG_INFO(msg) LOG(msg, LogLevel::kINFO)
#define LOG_WARNING(msg) LOG(msg, LogLevel::kWARNING)
#define LOG_ERROR(msg) LOG(msg, LogLevel::kERROR)

namespace parser {

class Context {
 public:
    Context(ILogger* log) : mLogger(log) {}
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

#endif  // CONTEXT_H
