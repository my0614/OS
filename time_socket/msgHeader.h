#ifndef __MSG_HEADER_H__
#define __MSG_HEADER_H__

// define PORT
#define PORT_SERVER_S 2001
#define PORT_SERVER_R 2002
#define PORT_CLIENT_S 2003
#define PORT_CLIENT_R 2004


// define msg id
#define reqGetTime 0x00020001
#define rspGetTime 0x00020002
#define reqSysInfo 0x00020003
#define rspSysInfo 0x00020004

// define msg structure
#include <arpa/inet.h>

inline long ntoh64(long x)
{
	return (((long)ntohl(0xFFFFFFFF&x))<<32) + ((long)ntohl(x>>32));
}

inline long hton64(long x)
{
	return (((long)htonl(0xFFFFFFFF&x))<<32) + ((long)htonl(x>>32));
}

inline unsigned long ntoh64(unsigned long x)
{
	return (((unsigned long)ntohl(0xFFFFFFFF&x))<<32) + ((unsigned long)ntohl(x>>32));
}

inline unsigned long hton64(unsigned long x)
{
	return (((unsigned long)htonl(0xFFFFFFFF&x))<<32) + ((unsigned long)htonl(x>>32));
}

inline int Write(int x)                               { return (htonl(x));  }
inline unsigned int Write(unsigned int x)             { return (htonl(x));  }
inline short int Write(short int x)                   { return (htons(x));  }
inline short unsigned int Write(short unsigned int x) { return (htons(x));  }
inline long Write(long x)                             { return (hton64(x)); }
inline unsigned long Write(unsigned long x)           { return (hton64(x)); }

inline int Read(int x)                                { return (ntohl(x));  }
inline unsigned int Read(unsigned int x)              { return (ntohl(x));  }
inline short int Read(short int x)                    { return (ntohs(x));  }
inline short unsigned int Read(short unsigned int x)  { return (ntohs(x));  }
inline long Read(long x)                              { return (ntoh64(x)); }
inline unsigned long Read(unsigned long x)              { return (ntoh64(x)); }

struct msgHeader
{
	int cmdId;
	int dummy;
};

inline void Write(struct msgHeader &x)
{
	x.cmdId = Write(x.cmdId);
}

inline void Read(struct msgHeader &x)
{
	x.cmdId = Read(x.cmdId);
}

struct dataTime
{
	long time;
	int retValue;
	int dummy;
};

inline void Write(struct dataTime &x)
{
	x.time = Write(x.time);
	x.retValue = Write(x.retValue);
}

inline void Read(struct dataTime &x)
{
	x.time = Read(x.time);
	x.retValue = Read(x.retValue);
}

struct msgTime
{
	struct msgHeader hdr;
	struct dataTime  data;
};

inline void Write(struct msgTime &x)
{
	Write(x.hdr);
	Write(x.data);
}

inline void Read(struct msgTime &x)
{
	Read(x.hdr);
	Read(x.data);
}
////

struct dataSysInfo
{
	char hostname[64];
	unsigned long totalram;
	unsigned long freeram;
	int retValue;
	int dummy;
};

inline void Write(struct dataSysInfo &x)
{
	x.totalram = Write(x.totalram);
	x.freeram = Write(x.freeram);
	x.retValue = Write(x.retValue);
}

inline void Read(struct dataSysInfo &x)
{
	x.totalram = Read(x.totalram);
	x.freeram = Read(x.freeram);
	x.retValue = Read(x.retValue);
}

struct msgSysInfo
{
	struct msgHeader hdr;
	struct dataSysInfo data;
};

inline void Write(struct msgSysInfo &x)
{
	Write(x.hdr);
	Write(x.data);
}

inline void Read(struct msgSysInfo &x)
{
	Read(x.hdr);
	Read(x.data);
}



#endif // __MSG_HEADER_H__

