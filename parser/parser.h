#ifndef ONNXPARSER_H
#define ONNXPARSER_H

#include <assert.h>

#include <sstream>
#include <string>
#include <vector>

namespace parser {

enum class LogLevel { kVERBOSE, kDEBUG, kINFO, kWARNING, kERROR };

class ILogger {
 public:
    virtual ~ILogger(){};

 public:
    virtual void log(LogLevel level, std::string msg) = 0;
};

class Context;

typedef std::pair<std::string, std::string> NodeAttr;

struct Node_t {
    std::string mName;
    std::string mType;
    std::vector<std::string> mInputs;
    std::vector<std::string> mOutputs;
    std::vector<NodeAttr> mAttrs;
};

class Parser {
 public:
    Parser(ILogger* logger);
    ~Parser();

 public:
    bool open(std::string path);
    bool save();
    bool saveAs(std::string path);
    bool close();
    void profile();

    size_t getNodeSize() const;
    // All of Node idx is by toposort
    const Node_t& getNode(size_t idx) const;

    std::vector<std::string>& getInputs() const;
    std::vector<std::string>& getOutputs() const;
    std::vector<std::string>& getInitializers() const;

 private:
    bool loadBin(std::string path);
    bool saveBin(std::string path);

    bool init();

 private:
    // TODO: recorder the protobuf type
    Context* mCtx;
};

}  // namespace parser

#endif  // ONNXPARSER_H