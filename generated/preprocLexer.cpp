
// Generated from preproc.g4 by ANTLR 4.7.2


#include "preprocLexer.h"


using namespace antlr4;


preprocLexer::preprocLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

preprocLexer::~preprocLexer() {
  delete _interpreter;
}

std::string preprocLexer::getGrammarFileName() const {
  return "preproc.g4";
}

const std::vector<std::string>& preprocLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& preprocLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& preprocLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& preprocLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& preprocLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> preprocLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& preprocLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> preprocLexer::_decisionToDFA;
atn::PredictionContextCache preprocLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN preprocLexer::_atn;
std::vector<uint16_t> preprocLexer::_serializedATN;

std::vector<std::string> preprocLexer::_ruleNames = {
  u8"BEGIN_C_STYLE_COMMENT", u8"END_C_STYLE_COMMENT", u8"ADA_STYLE_COMMENT_DELIM", 
  u8"NEWLINE", u8"QUOTE", u8"CHAR"
};

std::vector<std::string> preprocLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> preprocLexer::_modeNames = {
  u8"DEFAULT_MODE"
};

std::vector<std::string> preprocLexer::_literalNames = {
  "", u8"'/*'", u8"'*/'", u8"'--'", "", u8"'\"'"
};

std::vector<std::string> preprocLexer::_symbolicNames = {
  "", u8"BEGIN_C_STYLE_COMMENT", u8"END_C_STYLE_COMMENT", u8"ADA_STYLE_COMMENT_DELIM", 
  u8"NEWLINE", u8"QUOTE", u8"CHAR"
};

dfa::Vocabulary preprocLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> preprocLexer::_tokenNames;

preprocLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x2, 0x8, 0x1e, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 
    0x4, 0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
    0x7, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x2, 0x2, 0x8, 0x3, 0x3, 0x5, 0x4, 0x7, 0x5, 0x9, 0x6, 
    0xb, 0x7, 0xd, 0x8, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x2, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x2, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x2, 0xb, 0x3, 0x2, 0x2, 0x2, 0x2, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x3, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5, 0x12, 0x3, 0x2, 0x2, 
    0x2, 0x7, 0x15, 0x3, 0x2, 0x2, 0x2, 0x9, 0x18, 0x3, 0x2, 0x2, 0x2, 0xb, 
    0x1a, 0x3, 0x2, 0x2, 0x2, 0xd, 0x1c, 0x3, 0x2, 0x2, 0x2, 0xf, 0x10, 
    0x7, 0x31, 0x2, 0x2, 0x10, 0x11, 0x7, 0x2c, 0x2, 0x2, 0x11, 0x4, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x13, 0x7, 0x2c, 0x2, 0x2, 0x13, 0x14, 0x7, 0x31, 
    0x2, 0x2, 0x14, 0x6, 0x3, 0x2, 0x2, 0x2, 0x15, 0x16, 0x7, 0x2f, 0x2, 
    0x2, 0x16, 0x17, 0x7, 0x2f, 0x2, 0x2, 0x17, 0x8, 0x3, 0x2, 0x2, 0x2, 
    0x18, 0x19, 0x4, 0xc, 0xf, 0x2, 0x19, 0xa, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x1b, 0x7, 0x24, 0x2, 0x2, 0x1b, 0xc, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 
    0xb, 0x2, 0x2, 0x2, 0x1d, 0xe, 0x3, 0x2, 0x2, 0x2, 0x3, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

preprocLexer::Initializer preprocLexer::_init;