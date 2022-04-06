#include <string>
#include <any>
#include <map>
#include <vector>

namespace layout {

struct Node_t {
    Node_t(double w, double h): mW(w), mH(h) {}
    double mW = 0;
    double mH = 0;
    double mX = 0;
    double mY = 0;
    std::any mHandle;
    std::map<std::string, std::any> mData;
};

struct Edge_t {
    Edge_t(Node_t* f, Node_t* t): mFrom(f), mTo(t) {}
    Node_t* mFrom = nullptr;
    Node_t* mTo = nullptr;
    std::any mHandle;
    std::map<std::string, std::any> mData;
};

class Layout {
public:
 Node_t* addNode(double w, double h) {
     mNodes.emplace_back(w, h);
     return addNodeImpl(&mNodes.back());
 }
 Edge_t* addEdge(Node_t* from, Node_t* to) {
     mEdges.emplace_back(from, to);
     return addEdgeImpl(&mEdges.back());
 }
 void layout() {
     layoutImpl();
 }

protected:
 virtual Node_t* addNodeImpl(Node_t* node) {
     return node;
 }
 virtual Edge_t* addEdgeImpl(Edge_t* edge) {
     return edge;
 }
 virtual void layoutImpl() {
     return;
 }

protected:
 std::vector<Node_t> mNodes;
 std::vector<Edge_t> mEdges;
};

}
