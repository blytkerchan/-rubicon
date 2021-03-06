#ifndef rubicon_compiler_unknowntype_hpp
#define rubicon_compiler_unknowntype_hpp

#include "typedescriptor.hpp"
#include <iostream>

namespace Vlinder { namespace Rubicon { namespace Compiler {
struct UnknownType : TypeDescriptor
{
	explicit UnknownType(SourceLocation const &source_location)
		: TypeDescriptor(source_location)
	{ /* no-op */ }

	virtual Tag getTag() const override { return { Tag::universal__, 0 };  }
	virtual std::shared_ptr< TypeDescriptor > visit(Resolver &resolver) override { return resolver.resolve(*this); }
	virtual void generateEncodeImplementation(std::ostream &os) const override;
	virtual void generateCopyConstructorImplementation(std::ostream &os) const override;
};
}}}

#endif



