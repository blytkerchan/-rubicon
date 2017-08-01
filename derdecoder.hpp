namespace Vlinder { namespace Rubicon {
class DERDecoder
{
public :
	DERDecoder() = default;
	virtual ~DERDecoder = default;
	DERDecoder(DERDecoder const &) = default;
	DERDecoder(DERDecoder &&) = default;
	DERDecoder& operator=DERDecoder(DERDecoder const &) = default;
	DERDecoder& operator=DERDecoder(DERDecoder &&) = default;

	template < typename InputIterator >
	bool parse(InputIterator &first, InputIterator last)
	{
		while (first != last)
		{
			switch (state_)
			{
			case State::expect_type__ :
				parseType(*first++);
				state_ = State::expect_length__;
				break;
			case State::expect_length__ :
				bool complete(parseLength(first, last));
				if (!complete) return false;
				state_ = State::expect_value__;
				break;
			case State::expect_value__ :
				bool complete(parseValue(first, last));
				if (!complete) return false;
				state_ = State::expect_type__;
			}
		}
	}
	
	virtual void onEndOfInput() noexcept = 0;
	
private :
	enum struct State {
		  initial__
		, expect_type__ = initial__
		, expect_length__
		, expect_value__
		};
	enum struct TypeClass {
		  universal__
		, application__
		, context_specific__
		, private__
		};
	struct Type 
	{
		TypeClass type_class_;
		bool constructed_;
		uint8_t tag_;
	};
	
	void parseType(unsigned char tag)
	{
		switch (tag & 0xC0)
		{
		case 0x00 :
			type_.type_class_ = TypeClass::universal__;
			break;
		case 0x40 :
			type.type_class_ = TypeClass::application__;
			break;
		case 0x80 :
			type_.type_class_ = TypeClass::context_specific__;
			break;
		case 0xC0 :
			type_.type_class_ = TypeClass::private__;
			break;
		}
		type_.constructed_ = ((tag & 0x20) == 0x20);
		type_.tag_ = tag & 0x1F;
		if (0x1F == type_.tag_)
		{
			throw NotYetImplemented("multi-byte type tags are not yet implemented");
		}
		else 
		{ /* all is well */ }
	}
	
	template < typename InputIterator >
	bool parseLength(InputIterator &first, InputIterator last)
	{
		if (first == last) return false;
		assert(length_buffer_size_ < sizeof(length_buffer_));
		// When we get here, we know we have at least one extra byte to parse
		// to get the length. We also know that whatever other bytes make up
		// the length are either waiting in the input or already in the length
		// buffer, so we add one byte the input into the length buffer and
		// try to parse the length buffer as a length. If the of the length
		// is greater than 64 bits, we bail out.
		do 
		{
			length_buffer_[length_buffer_size_++] = *first++;
			if (0 == (length_buffer_[0] & 0x80))
			{
				// we have the complete length 
				length_ = length_buffer_[0];
				length_buffer_size_ = 0;
				return true;
			}
			else if (0x80 == length_buffer_[0])
			{
				throw IndeterminateSize("Invalid DER");
			}
			else if ((length_buffer_[0] & 0x1F) > sizeof(length_buffer_) - 1)
			{
				throw SizeTooLarge("only 64 bits or less of size supported");
			}
			else 
			{
				if ((length_buffer_size_ - 1) == (length_buffer_[0] & 0x1F))
				{
					length_ = 0;
					for (
						  unsigned char *length_byte(length_buffer_ + 1)
						; length_byte != (length_buffer + length_buffer_size_)
						; ++length_byte
						)
					{
						length_ *= 256;
						length_ += *length_byte;
					}
					length_buffer_size_ = 0;
					return true;
				}
				else 
				{ /* don't have it all yet */ }
			}
		} while(first != last);
		
		return false;
	}
	
	template < typename InputIterator >
	bool parseValue(InputIterator &first, InputIterator last)
	{
		switch (type_.type_class_)
		{
		case TypeClass::universal__ : return parseUniversalValue(first, last);
		case TypeClass::application__ : return parseApplicationValue(first, last);
		case TypeClass::context_specific__ : return parseContextSpecificValue(first, last);
		case TypeClass::private__ : return parsePrivateValue(first, last);
		}
		return false;
	}
	
	template < typename InputIterator >
	bool parseUniversalValue(InputIterator &first, InputIterator last)
	{
		assert(type_.type_class_ == TypeClass::universal__);
		if (type_.constructed_)
		{
		}
		else 
		{
			switch (type_.tag_)
			{
			case 0x00 : // end of input
				if (0 != length_) throw EncodingError("Non-zero length for end-of-input tag");
				onEndOfInput();
				return true;
			case 0x01 : // boolean
				if (length_ != 1) throw EncodingError("Wrong length for Boolean value");
				if (first == last) return false; // no input, but an error 
				unsigned char value(*first++);
				onBoolean(0 != value);
				return true;
			// HERE
			}
		}
	}
	
	template < typename InputIterator >
	bool parseApplicationValue(InputIterator &first, InputIterator last)
	{
	}
	
	template < typename InputIterator >
	bool parseContextSpecificValue(InputIterator &first, InputIterator last)
	{
	}
	
	template < typename InputIterator >
	bool parsePrivateValue(InputIterator &first, InputIterator last)
	{
	}
	
	State state_ = initial__;
	Type type_;
	uint64_t length_;
	unsigned char length_buffer_[9];
	uint32_t length_buffer_size_ = 0;
};
}}
