#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#include "parser.h"

namespace parser {

namespace {
enum NodeState { NODE_UNVISITED, NODE_ACTIVE, NODE_VISITED };

template <class Container>
bool get_post_order(size_t node_idx, Container const& nodes, std::unordered_map<std::string, size_t> const& node_map,
                    std::vector<NodeState>* node_states, std::vector<size_t>* order) {
    NodeState& node_state = node_states->at(node_idx);
    if (node_state == NODE_ACTIVE) {
        // cerr << "ERROR: Graph contains a cycle" << endl;
        return false;
    } else if (node_state == NODE_VISITED) {
        return true;
    } else {
        node_state = NODE_ACTIVE;
        for (auto const& input : nodes.Get(node_idx).input()) {
            if (!node_map.count(input)) {
                continue;
            }
            size_t input_node_idx = node_map.at(input);
            if (!get_post_order(input_node_idx, nodes, node_map, node_states, order)) {
                return false;
            }
        }
        node_state = NODE_VISITED;
        order->push_back(node_idx);
    }
    return true;
}
}  // namespace

template <class Container>
bool toposort(Container const& nodes, std::vector<size_t>* order) {
    std::unordered_map<std::string, size_t> node_map;
    for (size_t i = 0; i < (size_t)nodes.size(); ++i) {
        for (auto const& output : nodes.Get(i).output()) {
            if (!node_map.emplace(output, i).second) {
                // LOG_ERROR("Output name is not unique: " << output);
                return false;
            }
        }
    }
    order->reserve(nodes.size());
    std::vector<NodeState> node_states(nodes.size(), NODE_UNVISITED);
    for (size_t i = 0; i < (size_t)nodes.size(); ++i) {
        if (!get_post_order(i, nodes, node_map, &node_states, order)) {
            return false;
        }
    }
    return true;
}

template <class Container>
bool parseNode(Container const& inNode, Node_t& outNode) {
    outNode.mName = inNode.name();
    outNode.mType = inNode.op_type();
    outNode.mInputs.assign(inNode.input().begin(), inNode.input().end());
    outNode.mOutputs.assign(inNode.output().begin(), inNode.output().end());
    auto& attrs = outNode.mAttrs;
    for (auto iter = inNode.attribute().begin(); iter != inNode.attribute().end(); iter++) {
        attrs.emplace_back(iter->name(), std::to_string(iter->type()));
    }
    return true;
}

}  // namespace parser

#endif  // UTILS_H
