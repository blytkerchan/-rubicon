# -Rubicon Proof-of-concept ASN.1 code.

This project is mostly proof-of-concept at the moment. The goal is to show that "DER code ain't that bad".

## Preparing the build environment

You need a standard Vlinder development environment, which means an LTS Ubuntu (currently 18.04) with:

 $ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
      build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
      xz-utils debianutils iputils-ping libsdl1.2-dev xterm

and the latest Boost installed in ~/opt/boost-<version>, which you will need to tell CMake about using the
`-DBOOSTROOT=${HOME}/opt/boost<version>` option at the command-line

Additionally, you need uuid-dev:

 $ sudo apt-get install uuid-dev

and the vlinder/antlr4 Docker appliance

 $ docker pull vlinder/antlr4

## Notes about building

* Parallel builds are broken at the moment. This is due to the way part of the code is generated, and how part of the C++ runtime for the code generator is built as an "external" dependency. If someone wants to contribute a fix, please feel free to do so. You will need to fill out a CLA and a copyright disclaimer before I can look at any contributions, though.

## Running the test cases

The test cases need to believe Rubicon is installed in order to work. They don't need Rubicon to be installed on the system, though: just staging it is sufficient. To stage Rubicon to run the test cases, ddo the following:

 $ make && make install DESTDIR=stage
 $ path/to/tests/try\_testcases.py path/to/tests/testcases.csv -s stage

At the time of this writing, one test case is *expected* to fail: it tests that the compiler detects an error in the input file. By the time you read this, there may be more of those.

## About ASN.1

ASN.1, or Abstract Syntax Notation 1, is a domain-specific language (DSL) that consists of a human-readable schema language and several machine-readable representations for data encoded according to a schema described by that schema language.

ASN.1, as a DSL is immensely annoying, but it is also a well-accepted industry standard used in the likes of X.509 (the standards that govern the security of the Internet), and IEC 61850 (a suite of standards used in power systems automation, based mostly on XML schemas, but using ASN.1 over MMS as a transport).

ASN.1 is annoying because its schema language, which describes such things as what messages are expected to contain, is very flexible (which makes it harder to get it right and validate its interpretation) and had a few half-hearted and misguided attempts at encoding semantics in the type system. For example, it has a plethora of string types, most of which are equivalent to one another but all of which differ in subtle ways.

Further, there are several ways to encode data as described by ASN.1, some of which are almost indistinguishable from each other, but again differ in subtle ways. The ones normalised by ASN.1 are BER, DER, CER, PER and XER. The only close-to-sane one in the bunch is DER because *it*, at least, is unambiguous.

## Inception

The French have an expression: "coup de tête", which translates roughly to "a rash decision" but isn't quite as rash (in the negative sense), nor quite as deliberated as a decision ought to be. 

Anyway, there was a modern-day equivalent of a bike shed discussion (#random channel on Slack) that started with ASN.1 and fairly quickly veered to error handling in Python, which had Adam, who had started the discussion about ASN.1, "quietly back away from the bike shed". A few days later, Adam said "ASN.1 is a terrible DSL for security oriented message definitions. Way too complex. Security message/file formats must be simpler." on [Twitter] (https://twitter.com/jadamcrain/status/891732011773284352). This started a brief discussion in which I ended up defending DER (which is, of course, my own fault: I said "The problem with ASN.1 is specific (too many variants of too many types, no guidance when to use which). DER is not the problem." [here](https://twitter.com/blytkerchan/status/891797275768479744)).

I do like DER as an encoding: it's fairly simple and consistent, and doesn't allow for some of the corner cases that BER allows for. The encoding consistently encodes a type, followed by a length and a value. The type is typically encoded in a single octet (and there are very few valid use-cases where that would not be the case, so in this decoder I decided not to support them), the length is always encoded in as few octets as possible and, while ASN.1 doesn't specify a maximum size for any object, am implementation can reasonably be expected to impose limits on the gratuitous use of its resources. The DER decoder in this code limits the size of the length field to 64 bits, which is probably more than necessary. DER further limits the encoder's options in encoding the length more than BER does, as BER allows the encoder to not specify the length at all (in some cases) but simply add an end-of-contents marker at the end of the encoded contents. The contents of such an encoded value aren't exactly freeform either: the encoding rules are fairly straightforward for most value types (reals being a notable exception).

The problem with implementing a DER encoder is that, to do it right, you have to have a good idea of what exactly it is you're doing: you basically have to have done it before. The pitfalls are many, because so much is left unspecified or as a choice to the encoder. For example, a bit string is either primitive or constructed, at the encoder's option. Semantically, a constructed bit string is supposed to be a bit string that consists of more than one bit string (which BER allows, but DER does not). Syntactically, there is really no difference between primitive and constructed types. The -Rubicon decoder ignores the "constructed" bit for bit strings (and several other types of strings). The implementation choices you make, as Dan Kaminsky [rightly pointed out] (https://twitter.com/dakami/status/892128640279785473), affect the interoperability of the parser with other implementations. Interoperability is important because you rarely get to pick the implementation other people use, and you still need to be able to communicate with them. 

Now, Dan pointed this out (or rather, suggested I remember my implementation choices) because I had decided to implement something. When this discussion happened over Twitter, I was just coming out of a four-day monastery retreat so I was well-rested and remarkably zen. The discussion started just after the final "complies" of that Sunday evening, which was also the first time in a few days I looked at my Twitter feed. It didn't take long for Adam to CC a few others who I think he expected to agree with him about the short comings of ASN.1, so I ended up debating (which is a nice pass-time) and, as is my wont, taking up the contrary position.

The discussion picked up as I was pulling out of the monastery store, where I'd picked up a box of chocolates. Before starting to drive, I read my Twitter feed again, replied to the latest tweet and started off back home.

The discussion went on in the way back home, when I checked my Twitter feed while getting a cup of coffee (which I ended up doing a few times) and at one point I decided to pull over, download X.690 and set up the skeleton of a DER decoder. I stopped for about thirty minutes, wrote about 140 lines of code on my iPad and drove on home. Once I got home, I read what I'd written, made a few minor corrections and decided two things: firstly, that I was right and DER is not the problem, and secondly that the code I'd written earlier that day was worth keeping and spending a bit more time on. My "coup de tête" from earlier that day had become a project.

## Design 

The DERDecoder class is a syntactic scanner: it consumes input from an input iterator and decodes the Type-Length-Value tuples out finds, handing the decoded values to a derived class.

The iterators it expects are standard input iterators: single-pass, each position read exactly once. This is the weakest category of iterators one can read from and therefore allows the greatest flexibility to the calling code as to where to get the data from. When values read from the input need to be re-read, they are stored on an internal parse buffer, the size of which is dictated by the number of bits that the implementation should be able to read for an integer value. That value must be at least 64, and defaults to 2048. With that default, the parse buffer is 256 bytes in size, which makes the whole decoder about 280 bytes in terms of its state. 

The decoder does not decode extended types, nor does it accept objects that take more than 64 bytes to encode their size, or objects of indeterminate size. DER mandates that all objects shall have determinate size, and extenders types are outside the scope of a general-purpose decoder, so both of these restrictions are easy to justify. 

The decoder also checks for the internal consistency of the TLV encodings, when it can. For example, a type that must have N content octets by definition shall have N content octets - otherwise the decoder will throw an EncodingError exception. Things that are valid DER but not supported, like base-10 reals, result in a DecodingError exception. 

As for exceptions: I usually design my code to be able to live without them, by adding a nothrow version of every function. I might still do that, but I wrote the start of this code on the side of the road, in a car, with half a muffin and a cup of coffee, so exceptions there are, and exceptions there will be. The code is exception-safe in that it provides the Strong guarantee: the parser will have reset to expecting a type encoding whenever it throws an exception.
