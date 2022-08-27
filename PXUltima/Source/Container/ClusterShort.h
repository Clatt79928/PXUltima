#ifndef ClusterShortDEFINED
#define ClusterShortDEFINED

// Detect current endianess on this system and then use #if
#define MakeShort(a, b) MakeShortLE(a, b)

#define MakeShortBE(a, b) (((unsigned short)a << 8) | ((unsigned short)b))
#define MakeShortLE(a, b) (((unsigned short)a) | ((unsigned short)b << 8))

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct ClusterShort_
	{
		union
		{
			struct
			{
				unsigned char A;
				unsigned char B;
			};

			unsigned char Data[2];

			unsigned short Value;
		};
	}ClusterShort;

#ifdef __cplusplus
}
#endif

#endif