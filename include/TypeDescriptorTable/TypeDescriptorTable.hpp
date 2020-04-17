#ifndef TYPE_DESCRIPTOR_TABLE_HPP
#define TYPE_DESCRIPTOR_TABLE_HPP

#include <unordered_map>
#include <string>
#include "AST/Node.hpp"
#include "TypeDescriptorTable/TypeDescriptor.hpp"


//Singleton
class TypeDescriptorTable {
	private:
		TypeDescriptorTable() { } // Constructor
		std::unordered_map<std::string, TypeDescriptor> typeTable;
	public:
		static TypeDescriptorTable& getInstance() {
			// Guaranteed to be destroyed. Instantiated on first use.
			static TypeDescriptorTable instance;
			return instance;
		}
		
		void append(
				std::string typeName,
				std::string category,
				std::string baseType,
				std::string baseTypeCategory,
				Node *node
		);
		TypeDescriptor getTypeDescriptor(std::string typeName);

		TypeDescriptorTable(TypeDescriptorTable const&) = delete;
		void operator=(TypeDescriptorTable const&) = delete;
};

#endif
