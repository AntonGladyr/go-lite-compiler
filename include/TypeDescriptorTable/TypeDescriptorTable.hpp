#ifndef TYPE_DESCRIPTOR_TABLE_HPP
#define TYPE_DESCRIPTOR_TABLE_HPP

#include <unordered_map>
#include <string>
#include "AST/Node.hpp"

//Singleton
class TypeDescriptorTable {
	private:
		TypeDescriptorTable() { } // Constructor
		std::unordered_map<std::string, std::string> typeTable;
	public:
		static TypeDescriptorTable& getInstance() {
 			// Guaranteed to be destroyed. Instantiated on first use.
 			static TypeDescriptorTable instance;
 			return instance;
 		}
		
		void append(
			std::string typeName,
			std::string targetTypeName
		);
		
		std::string getTypeDescriptor(std::string typeName);
};

#endif
