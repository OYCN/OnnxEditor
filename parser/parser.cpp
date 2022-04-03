#include "parser.h"

#include <google/protobuf/text_format.h>

#include <fstream>

#include "context.h"
#include "utils.h"

namespace parser {

Parser::Parser(ILogger* logger) { mCtx = new Context(logger); }
Parser::~Parser() { delete mCtx; }

bool Parser::loadBin(std::string path) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    if (!fin) {
        LOG_ERROR("Could not open file " << std::string(path));
        return false;
    }
    bool ret = mCtx->mOnnxModel.ParseFromIstream(&fin);
    return ret;
}

bool Parser::saveBin(std::string path) {
    std::ofstream fout(path, std::ios::out | std::ios::binary);
    if (!fout) {
        LOG_ERROR("output file : " << path << " is not found.");
        return false;
    }

    bool ret = mCtx->mOnnxModel.SerializeToOstream(&fout);
    return ret;
}
bool Parser::open(std::string path) {
    // TODO: load txt profobuf
    mCtx->mFilePath = path;
    if (!loadBin(path)) {
        LOG_ERROR("File Open Error");
        return false;
    }
    if (!init()) {
        LOG_ERROR("Onnx Parser Error");
        return false;
    }
    return true;
}

bool Parser::save() {
    // TODO: load txt profobuf
    if (mCtx->mFilePath.size() == 0) {
        return false;
    }
    bool ret = saveBin(mCtx->mFilePath);
    return ret;
}

bool Parser::saveAs(std::string path) {
    // TODO: load txt profobuf
    bool ret = saveBin(path);
    return ret;
}

bool Parser::close() {
    // TODO: ensure model has been del
    mCtx->mFilePath.clear();
    mCtx->mOnnxModel.Clear();
    return true;
}

void Parser::profile() {
    const int64_t opset_version =
        (mCtx->mOnnxModel.opset_import().size() ? mCtx->mOnnxModel.opset_import(0).version() : 0);
    auto ir_version_raw = mCtx->mOnnxModel.ir_version();
    int onnx_ir_major = ir_version_raw / 1000000;
    int onnx_ir_minor = ir_version_raw % 1000000 / 10000;
    int onnx_ir_patch = ir_version_raw % 10000;
    auto ir_version =
        std::to_string(onnx_ir_major) + "." + std::to_string(onnx_ir_minor) + "." + std::to_string(onnx_ir_patch);
    LOG_INFO("----------------------------------------------------------------");
    LOG_INFO("Input filename:   " << mCtx->mFilePath);
    LOG_INFO("ONNX IR version:  " << ir_version);
    LOG_INFO("Opset version:    " << opset_version);
    LOG_INFO("Producer name:    " << mCtx->mOnnxModel.producer_name());
    LOG_INFO("Producer version: " << mCtx->mOnnxModel.producer_version());
    LOG_INFO("Domain:           " << mCtx->mOnnxModel.domain());
    LOG_INFO("Model version:    " << mCtx->mOnnxModel.model_version());
    LOG_INFO("Doc string:       " << mCtx->mOnnxModel.doc_string());
    LOG_INFO("----------------------------------------------------------------");
}

bool Parser::init() {
    auto& graph = mCtx->mOnnxModel.graph();
    auto& nodes = graph.node();
    LOG_DEBUG("Start TopoSort");
    if (!toposort(nodes, &mCtx->mTopoOrder)) {
        LOG_ERROR("Topo Sort Failed");
        return false;
    }
    LOG_DEBUG("TopoSort Done");
    if (mCtx->mTopoOrder.size() != nodes.size()) {
        LOG_ERROR("TopoSort size is " << mCtx->mTopoOrder.size() << ", But nodes size is " << nodes.size());
        return false;
    }
    LOG_DEBUG("Record Inputs");
    mCtx->mInputs.clear();
    for (auto i : graph.input()) {
        mCtx->mInputs.emplace_back(i.name());
    }
    LOG_DEBUG("Record Inputs Done");
    LOG_DEBUG("Record Outputs");
    mCtx->mOutputs.clear();
    for (auto i : graph.output()) {
        mCtx->mOutputs.emplace_back(i.name());
    }
    LOG_DEBUG("Record Outputs Done");
    LOG_DEBUG("Record Initializers");
    mCtx->mInitializers.clear();
    for (auto i : graph.initializer()) {
        mCtx->mInitializers.emplace_back(i.name());
    }
    LOG_DEBUG("Record Initializers Done");
    LOG_DEBUG("Record Nodes");
    mCtx->mNodes.resize(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
        if (!parseNode(nodes.Get(i), mCtx->mNodes[i])) {
            LOG_ERROR("Parse Node Failed at: " << i);
            return false;
        }
        // LOG_INFO("Parsed: [" << i << "]" << mCtx->mNodes[i].mName);
    }
    LOG_DEBUG("Record Nodes Done");
    return true;
}

size_t Parser::getNodeSize() const { return mCtx->mTopoOrder.size(); }
const Node_t& Parser::getNode(size_t idx) const { return mCtx->mNodes[mCtx->mTopoOrder[idx]]; }
std::vector<std::string>& Parser::getInputs() const { return mCtx->mInputs; }
std::vector<std::string>& Parser::getOutputs() const { return mCtx->mOutputs; }
std::vector<std::string>& Parser::getInitializers() const { return mCtx->mInitializers; }

}  // namespace parser
