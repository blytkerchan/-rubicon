#include "unknowntype.hpp"

using namespace std;

namespace Vlinder { namespace Rubicon { namespace Compiler {
/*virtual */void UnknownType::generateEncodeImplementation(ostream &os) const/* override*/
{
	os << "//TODO " << typeid(*this).name() << endl;
}
/*virtual */void UnknownType::generateCopyConstructorImplementation(ostream &os) const/* override*/
{
	os << "//TODO " << typeid(*this).name() << endl;
}

}}}






