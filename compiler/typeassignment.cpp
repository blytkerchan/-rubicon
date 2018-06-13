#include "typeassignment.hpp"

namespace Vlinder { namespace Rubicon { namespace Compiler {
void TypeAssignment::generateCopyConstructorImplementation(std::ostream &os) const
{
	if (hasOptionalMembers())
	{
		os << getName() << "::" << getName() << "(" << getName() << " const &other)\n{\n";
		type_descriptor_->generateCopyConstructorImplementation(os);
		os << "}\n";
	}
	else
	{ /* no optional members - default copy constructor */ }
}
void TypeAssignment::generateDestructorImplementation(std::ostream &os) const
{
	if (hasOptionalMembers())
	{
		os << getName() << "::~" << getName() << "()\n{\n";
		type_descriptor_->generateDestructorImplementation(os);
		os << "}\n";
	}
	else
	{ /* no optional members - default copy constructor */ }
}
void TypeAssignment::generateAssignmentOperatorImplementation(std::ostream &os) const
{
	if (hasOptionalMembers())
	{
		os <<
			getName() << "& " << getName() << "::operator=(" << getName() << " const &other)\n"
			"{\n"
			"\t" << getName() << " temp(other);\n"
			"\treturn swap(temp);\n"
			"}\n";
	}
	else
	{ /* no optional members - default copy constructor */ }
}
}}}

