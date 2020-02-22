#include "Node.hpp"
#include "StatementEnum.hpp"

class Statement : public Node {
	public:
		StatementKind kind;	
};
