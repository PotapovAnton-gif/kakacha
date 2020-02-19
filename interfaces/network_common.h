#ifndef SRC_INTERFACES_NETWORK_COMMON_H_
#define SRC_INTERFACES_NETWORK_COMMON_H_

#include "common.h"

namespace Network {

using namespace std;


/*
 * Network delay (ping). Measured in ms.
 */
using Ping = unsigned long int;

/*
 * A single byte.
 */
using Byte = unsigned char;

class PacketReader;
class PacketWriter;


/*
 * A network packet. Information transferred over the network connections is
 * separated into packets.
 *
 * A packet contains a body and a type. Type can be used to identify
 * packets with different meaning. Body is a Byte array that can be used to
 * transfer data. Body can be empty (have length 0).
 *
 * Packets are immutable objects.
 */
class Packet {
public:

	/*
	 * Packet type, a Byte. Types 0x00-0x0F and 0xFF are reserved for service
	 * traffic - they should never be sent and will never be received by client
	 * code.
	 */
	using Type = Byte;

private:

	/*
	 * Type of this packet.
	 */
	const Type type;

	/*
	 * Byte array that stores this packet's body.
	 */
	const Byte * const body;

	/*
	 * Length of this packet's body.
	 */
	const size_t length;

public:

	/*
	 * Creates a new packet. It is preferable to use PacketWriter to construct
	 * Packets.
	 *
	 * Type - type of the packet.
	 * body - body as a Byte array. The passed pointer will be reused and
	 *     delete[]d by the created Packet.
	 * length - length of body.
	 */
	Packet(Type, const Byte *body, size_t length);
	~Packet();

	/*
	 * Returns the type of this packet.
	 */
	Type getType() const;

	/*
	 * Returns the body of this packet. Use Packet::getReader() for parsing the
	 * body conveniently.
	 */
	const Byte* getBody() const;

	/*
	 * Returns the length of the body of this packet. Use Packet::getReader()
	 * for parsing the body conveniently.
	 */
	size_t getLength() const;

	/*
	 * Constructs a new PacketReader that is set up to read this packet.
	 */
	PacketReader getReader() const;
};

/*
 * A utility class for parsing packets. Create with Packet::getReader().
 */
class PacketReader {
public:

	/*
	 * Reads a single Byte from the packet body. This reader's position is
	 * incremented by 1 on success. Behaviour is undefined if no more Bytes
	 * could be read.
	 */
	Byte readByte();

	/*
	 * Returns this readers's current position. Position is set to 0 by default.
	 * Position is always within [0; getLength()], where position getLength()
	 * indicates that no more Bytes can be read.
	 */
	size_t getPosition() const;

	/*
	 * Sets this reader's position to the specified value. Behaviour is
	 * undefined if the position is not within [0; getLength()].
	 */
	void setPosition(size_t);

	/*
	 * Returns the length of the body of the packet.
	 */
	void getLength() const;

	/*
	 * Reads an int from the packet body. This reader's position is incremented
	 * by 4 on success. Behaviour is undefined if no more Bytes could be read.
	 */
	int readInt();

	/*
	 * Reads a string previously encoded with ParserWriter::writeString() from
	 * the packet body. This reader's position is incremented by at least 4 on
	 * success. Behaviour is undefined if no more Bytes could be read or the
	 * string is not encoded properly.
	 */
	string readString();

	/*
	 * Returns true if and only if the next "bytes" Bytes can be read safely.
	 */
	bool hasMore(size_t bytes = 1) const;

	/*
	 * Marks this position by adding it to the mark stack.
	 * Used with PacketReader::reset().
	 */
	void mark();

	/*
	 * Changes the position of this reader to the top of the mark stack and
	 * removes the that top.
	 *
	 * Behaviour is undefined if no marks are available.
	 *
	 * Marks can be set with PacketReader::mark(). See Packet::forget().
	 *
	 * Example use:
	 *
	 * PacketReader r = ...
	 * r.mark();            // Position 0 is marked
	 * int a = r.readInt();
	 * r.mark();            // Position 4 is marked, 0 is still marked
	 * int b = r.readInt();
	 * r.reset();           // Mark 4 has been marked last, position is now 4,
	 *                      //     0 is still marked
	 * r.readInt() == b;    // true
	 * r.reset();
	 * r.readInt() == a;    // true
	 */
	void reset();

	/*
	 * Removes the top mark from the mark stack, potentially exposing previous
	 * marks.
	 */
	void forget();

	/*
	 * Returns the type of the packet.
	 */
	Packet::Type getType();
};

class PacketWriter {
public:
	PacketWriter(Packet::Type);

	void writeByte(Byte);
	Packet* toPacket();

	void writeInt(int);
	void writeString(string);
};


} /* namespace Network */

#endif /* SRC_INTERFACES_NETWORK_COMMON_H_ */
