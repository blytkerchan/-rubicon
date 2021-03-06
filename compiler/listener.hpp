#ifndef rubicon_compiler_listener_hpp
#define rubicon_compiler_listener_hpp

#include "../generated/asn1BaseListener.h"
#include "arcidentifier.hpp"
#include "constraint.hpp"
#include "directory.hpp"
#include "namednumber.hpp"
#include "namedtype.hpp"
#include "oidcomponent.hpp"
#include "tag.hpp"
#include "typedescriptor.hpp"
#include "value.hpp"
#include <ostream>
#include <memory>

namespace Vlinder { namespace Rubicon { namespace Compiler {
struct RestrictedCharacterStringValue;
class Listener : public ::asn1BaseListener, public Directory
{
public :
	enum struct TagDefault {
		  explicit_tags__
		, implicit_tags__
		, automatic_tags__
		};

	Listener();

protected :
	virtual void exitModule_identifier(asn1Parser::Module_identifierContext *ctx) override;
	virtual void exitEncoding_reference_default(asn1Parser::Encoding_reference_defaultContext *ctx) override;
	virtual void exitExplicit_tags(asn1Parser::Explicit_tagsContext *ctx) override;
	virtual void exitImplicit_tags(asn1Parser::Implicit_tagsContext *ctx) override;
	virtual void exitAutomatic_tags(asn1Parser::Automatic_tagsContext *ctx) override;
	virtual void exitExtension_default(asn1Parser::Extension_defaultContext *ctx) override;
	virtual void exitEncoding_control_section(asn1Parser::Encoding_control_sectionContext *ctx) override;
	virtual void exitExports(asn1Parser::ExportsContext *ctx) override;
	virtual void exitImports(asn1Parser::ImportsContext *ctx) override;
	virtual void exitAssignment_list(asn1Parser::Assignment_listContext *ctx) override;

public :
	std::string getModuleName() const { return module_name_; }
	TagDefault getTagDefault() const { return tag_default_; }
	bool isModuleTypesExtensibilityImplied() const { return module_types_extensibility_implied_; }
	bool exportAll() const { return export_all_; }

private :
	ObjectIdentifier parseObjectIdentifier(asn1Parser::Object_identifier_valueContext *ctx);
	unsigned int parseNumber(antlr4::tree::TerminalNode *node);
	TypeAssignment parseTypeAssignment(asn1Parser::Type_assignmentContext *ctx);
	std::shared_ptr< TypeDescriptor > parseType(asn1Parser::TypeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseBuiltinType(asn1Parser::Builtin_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseBitStringType(asn1Parser::Bit_string_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseBooleanType(asn1Parser::Builtin_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseCharacterStringType(asn1Parser::Character_string_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseChoiceType(asn1Parser::Choice_typeContext *ctx);
	NamedType parseNamedType(asn1Parser::Named_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseEnumeratedType(asn1Parser::Enumerated_typeContext *ctx);
	NamedNumber parseNamedNumber(asn1Parser::Named_numberContext *ctx);
	long parseSignedNumber(asn1Parser::Signed_numberContext *ctx);
	std::shared_ptr< TypeDescriptor > parseIntegerType(asn1Parser::Integer_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseSequenceOrSetType(asn1Parser::Sequence_or_set_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseSequenceOrSetOfType(asn1Parser::Sequence_or_set_of_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parsePrefixedType(asn1Parser::Prefixed_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseDefinedType(asn1Parser::Defined_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseUsefulType(asn1Parser::Useful_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseSelectionType(asn1Parser::Selection_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseContrainedType(asn1Parser::Constrained_typeContext *ctx);
	std::shared_ptr< TypeDescriptor > parseReferencedType(asn1Parser::Referenced_typeContext *ctx);
	Constraint parseConstraint(asn1Parser::ConstraintContext *ctx);

	Tag parseTag(asn1Parser::TagContext *ctx);

	std::shared_ptr< Value > parseValue(std::shared_ptr< TypeDescriptor > const &type, asn1Parser::ValueContext *ctx);
	std::shared_ptr< Value > parseValue(asn1Parser::ValueContext *ctx);
	std::shared_ptr< Value > parseBuiltinValue(std::shared_ptr< TypeDescriptor > const &type, asn1Parser::Builtin_valueContext *ctx);
	std::shared_ptr< Value > parseDefinedValue(std::shared_ptr< TypeDescriptor > const &type, asn1Parser::Defined_valueContext *ctx);
	std::shared_ptr< Value > parseBitStringValue(std::shared_ptr< TypeDescriptor > const &type, asn1Parser::Bit_string_valueContext *ctx);
	std::pair< std::vector< unsigned char >, unsigned int > parseBString(antlr4::tree::TerminalNode *bstring);
	std::pair< std::vector< unsigned char >, unsigned int > parseHString(antlr4::tree::TerminalNode *hstring);

	std::shared_ptr< Value > parseBooleanValue(asn1Parser::Boolean_valueContext *ctx);
	std::shared_ptr< Value > parseCharacterStringValue(asn1Parser::Character_string_valueContext *ctx);
	std::shared_ptr< Value > parseRestrictedCharacterStringValue(asn1Parser::Restricted_character_string_valueContext *ctx);
	void parseCharacterStringList(RestrictedCharacterStringValue &retval, asn1Parser::Character_string_listContext *ctx);
	void parseQuadruple(RestrictedCharacterStringValue &retval, asn1Parser::QuadrupleContext *ctx);
	void parseTuple(RestrictedCharacterStringValue &retval, asn1Parser::TupleContext *ctx);

	std::shared_ptr< Value > parseUnrestrictedCharacterStringValue(asn1Parser::Unrestricted_character_string_valueContext *ctx);
	std::shared_ptr< Value > parseChoiceValue(asn1Parser::Choice_valueContext *ctx);
	std::shared_ptr< Value > parseEmbeddedPDVValue(asn1Parser::Embedded_pdv_valueContext *ctx);
	std::shared_ptr< Value > parseEnumeratedValue(asn1Parser::Enumerated_valueContext *ctx);
	std::shared_ptr< Value > parseIntegerValue(asn1Parser::Integer_valueContext *ctx);
	std::shared_ptr< Value > parseIRIValue(asn1Parser::Iri_valueContext *ctx);
	std::shared_ptr< Value > parseObjectIdentifierValue(asn1Parser::Object_identifier_valueContext *ctx);
	std::shared_ptr< Value > parseOctetStringValue(asn1Parser::Octet_string_valueContext *ctx);
	std::shared_ptr< Value > parseRealValue(asn1Parser::Real_valueContext *ctx);
	std::shared_ptr< Value > parseRelativeIRIValue(asn1Parser::Relative_iri_valueContext *ctx);
	std::shared_ptr< Value > parseRelativeOIDValue(asn1Parser::Relative_oid_valueContext *ctx);
	OIDComponent parseOIDComponent(asn1Parser::Relative_oid_componentsContext *ctx);

	std::shared_ptr< Value > parseSequenceValue(asn1Parser::Sequence_valueContext *ctx);
	std::shared_ptr< Value > parseNamedValue(asn1Parser::Named_valueContext *ctx);
	std::shared_ptr< Value > parseSequenceOfValue(asn1Parser::Sequence_of_valueContext *ctx);
	std::shared_ptr< Value > parseSetValue(asn1Parser::Set_valueContext *ctx);
	std::shared_ptr< Value > parseSetOfValue(asn1Parser::Set_of_valueContext *ctx);
	std::shared_ptr< Value > parseTimeValue(asn1Parser::Time_valueContext *ctx);

	ArcIdentifier parseArcIdentifier(asn1Parser::Arc_identifierContext *ctx);

	ValueAssignment parseValueAssignment(asn1Parser::Value_assignmentContext *ctx);

	static void emitWarning(antlr4::ParserRuleContext *ctx, char const *fmt, ...);
	static void emitWarning(antlr4::tree::TerminalNode *node, char const *fmt, ...);
	static void emitError(antlr4::ParserRuleContext *ctx, char const *fmt, ...);
	static void emitError(antlr4::tree::TerminalNode *node, char const *fmt, ...);

	// from parsing
	std::string module_name_;
	asn1Parser::Definitive_identificationContext *module_definitive_identification_ = nullptr;
	TagDefault tag_default_ = TagDefault::explicit_tags__;
	bool module_types_extensibility_implied_ = false;
	bool export_all_ = false;
};
}}}

#endif


