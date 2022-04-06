#include "common.h"
#include <ogdf/basic/Graph.h>

namespace layout {

class OgdfLayout: public Layout {
public:
 Node_t* addNodeImpl(Node_t* node) override;
 Edge_t* addEdgeImpl(Edge_t* edge) override;
 void layoutImpl() override;
private:
 ogdf::Graph mGraph;
};

}
