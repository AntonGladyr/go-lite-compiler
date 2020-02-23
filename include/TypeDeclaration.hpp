class TypeDeclaration : Declaration {
	public:
		std::string newType;
		std::string existingType;

		TypeDeclaration() { }
		TypeDeclaration(std::string newType, std::string existingType)
			: Declaration(k_declKindType), newType{newType}, existingType{existingType};
}
