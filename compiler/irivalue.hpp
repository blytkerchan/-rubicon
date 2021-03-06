#ifndef rubicon_compiler_irivalue_hpp
#define rubicon_compiler_irivalue_hpp

#include "value.hpp"
#include "arcidentifier.hpp"

namespace Vlinder { namespace Rubicon { namespace Compiler {
class IRIValue : public Value
{
public :
	IRIValue(SourceLocation const &source_location, bool relative = false)
		: Value(source_location)
		, relative_(relative)
	{ /* no-op */ }

	void add(ArcIdentifier const &arc_identifier)
	{
		arc_identifiers_.push_back(arc_identifier);
	}

	std::string getTypeName() const override { return "IRI"; }

	std::string generateInstance() const override { return "/*TODO*/"; }

private :
	bool relative_;
	std::vector< ArcIdentifier > arc_identifiers_;
};
}}}

#endif



