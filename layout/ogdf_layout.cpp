#include "ogdf_layout.h"

#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/FastHierarchyLayout.h>

namespace layout {

Node_t* OgdfLayout::addNodeImpl(Node_t* node) {
    ogdf::NodeElement* n = mGraph.newNode();
    node->mHandle = n;
    return node;
}
Edge_t* OgdfLayout::addEdgeImpl(Edge_t* edge) {
    auto node1 = std::any_cast<ogdf::NodeElement*>(edge->mFrom->mHandle);
    auto node2 = std::any_cast<ogdf::NodeElement*>(edge->mTo->mHandle);
    ogdf::EdgeElement* e = mGraph.newEdge(node1, node2);
    edge->mHandle = e;
    return edge;
}
void OgdfLayout::layoutImpl() {
    ogdf::GraphAttributes graphAttr(mGraph,
                            ogdf::GraphAttributes::nodeGraphics | ogdf::GraphAttributes::edgeGraphics |
                            ogdf::GraphAttributes::nodeLabel | ogdf::GraphAttributes::edgeStyle |
                            ogdf::GraphAttributes::nodeStyle | ogdf::GraphAttributes::nodeTemplate);
    for (const auto& node : mNodes) {
        auto handle = std::any_cast<ogdf::NodeElement*>(node.mHandle);
        auto w = node.mW;
        auto h = node.mH;
        graphAttr.width(handle) = w;
        graphAttr.height(handle) = h;
    }
    ogdf::SugiyamaLayout layout;
    ogdf::FastHierarchyLayout* ohl = new ogdf::FastHierarchyLayout;
    ohl->layerDistance(30);
    ohl->nodeDistance(25);
    layout.setLayout(ohl);

    layout.call(graphAttr);

    for (auto& node : mNodes) {
        auto handle = std::any_cast<ogdf::NodeElement*>(node.mHandle);
        node.mX = graphAttr.x(handle);
        node.mY = graphAttr.y(handle);
    }
}

}
