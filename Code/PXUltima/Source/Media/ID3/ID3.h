#ifndef ID3Include
#define ID3Include

#include <Media/PXType.h>
#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>

#define ID3TitleSize 30
#define ID3ArtistSize 30
#define ID3AlbumSize 30
#define ID3YearSize 4
#define ID3CommentSize 30

#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum ID3Version_
	{
		ID3VersionInvalid,
		ID3Versionv1x0,
		ID3Versionv1x1,
		ID3Versionv2x0,
		ID3Versionv2x2,
		ID3Versionv2x3,
		ID3Versionv2x4
	}
	ID3Version;

	typedef enum ID3v2xFrameTag_
	{
		ID3v2xFrameTagInvalid,

		AudioEncryption, // 4.20    AENC [[#sec4.20 | ]]
		AttachedPicture,//4.15    APIC[#sec4.15 ]
		Comments,//4.11    COMM[#sec4.11 Comments]
		CommercialFrame,//4.25    COMR[#sec4.25 Commercial frame]
		EncryptionMethodRegistration,//4.26    ENCR[#sec4.26 Encryption method registration]
		Equalization,//4.13    EQUA[#sec4.13 Equalization]
		EventTimingCodes,//4.6     ETCO[#sec4.6 Event timing codes]
		GeneralEncapsulatedObject,//4.16    GEOB[#sec4.16 General encapsulated object]
		GroupIdentificationRegistration,//4.27    GRID[#sec4.27 Group identification registration]
		InvolvedPeopleList,//4.4     IPLS[#sec4.4 Involved people list]
		LinkedInformation,//4.21    LINK[#sec4.21 Linked information]
		MusicCDIdentifier,//4.5     MCDI[#sec4.5 Music CD identifier]
		MPEGLocationLookupTable,//4.7     MLLT[#sec4.7 MPEG location lookup table]
		OwnershipFrame,//4.24    OWNE[#sec4.24 Ownership frame]
		PrivateFrame,//4.28    PRIV[#sec4.28 Private frame]
		PlayCounter,//4.17    PCNT[#sec4.17 Play counter]
		Popularimeter,//4.18    POPM[#sec4.18 Popularimeter]
		PositionSynchronisationFrame,//4.22    POSS[#sec4.22 Position synchronisation frame]
		RecommendedBufferSize,//4.19    RBUF[#sec4.19 Recommended buffer size]
		RelativeVolumeAdjustment,//4.12    RVAD[#sec4.12 Relative volume adjustment]
		Reverb,//4.14    RVRB[#sec4.14 Reverb]
		SynchronizedLyric,//4.10    SYLT[#sec4.10 Synchronized lyric / text]
		SynchronizedTempocodes,//4.8     SYTC[#sec4.8 Synchronized tempo codes]
		Album,//4.2.1   TALB[#TALB Album / Movie / Show title]
		BeatsPerMinute,//4.2.1   TBPM[#TBPM BPM(beats per minute)]
		Composer,//4.2.1   TCOM[#TCOM Composer]
		ContentType,//4.2.1   TCON[#TCON Content type]
		CopyrightMessage,//4.2.1   TCOP[#TCOP Copyright message]
		Date,//4.2.1   TDAT[#TDAT Date]
		PlaylistDelay,//4.2.1   TDLY[#TDLY Playlist delay]
		TaggingTime, // TDTG
		EncodedBy,//4.2.1   TENC[#TENC Encoded by]
		Lyricist,//4.2.1   TEXT[#TEXT Lyricist / Text writer]
		FileType,//4.2.1   TFLT[#TFLT File type]
		Time,//4.2.1   TIME[#TIME Time]
		ContentGroupDescription,//4.2.1   TIT1[#TIT1 Content group description]
		Title,//4.2.1   TIT2[#TIT2 Title / songname / content description]
		Subtitle,//4.2.1   TIT3[#TIT3 Subtitle / Description refinement]
		InitialKey,//4.2.1   TKEY[#TKEY Initial key]
		Language,//4.2.1   TLAN[#TLAN Language(s)]
		Length,//4.2.1   TLEN[#TLEN Length]
		MediaType,//4.2.1   TMED[#TMED Media type]
		OriginalAlbum,//4.2.1   TOAL[#TOAL Original album / movie / show title]
		OriginalFilename,//4.2.1   TOFN[#TOFN Original filename]
		OriginalLyricist,//4.2.1   TOLY[#TOLY Original lyricist(s) / text writer(s)]
		OriginalArtist,//4.2.1   TOPE[#TOPE Original artist(s) / performer(s)]
		OriginalReleaseYear,//4.2.1   TORY[#TORY Original release year]
		FileOwner,//4.2.1   TOWN[#TOWN File owner / licensee]
		LeadPerformer,//4.2.1   TPE1[#TPE1 Lead performer(s) / Soloist(s)]
		Band,//4.2.1   TPE2[#TPE2 Band / orchestra / accompaniment]
		Conductor,//4.2.1   TPE3[#TPE3 Conductor / performer refinement]
		InterpretedBy,//4.2.1   TPE4[#TPE4 Interpreted, remixed, or otherwise modified by]
		PartOfASet,//4.2.1   TPOS[#TPOS Part of a set]
		Publisher,//4.2.1   TPUB[#TPUB Publisher]
		TrackNumber,//4.2.1   TRCK[#TRCK Track number / Position in set]
		RecordingDates,//4.2.1   TRDA[#TRDA Recording dates]
		InternetRadioStationName,//4.2.1   TRSN[#TRSN Internet radio station name]
		InternetRadioStationOwner,//4.2.1   TRSO[#TRSO Internet radio station owner]
		Size,//4.2.1   TSIZ[#TSIZ Size]
		InternationalStandardRecordingCode,//4.2.1   TSRC[#TSRC ISRC(international standard recording code)]
		SoftwareHardwaresettingsUsedForEncoding,//4.2.1   TSSE[#TSEE Software / Hardware and settings used for encoding]
		Year,//4.2.1   TYER[#TYER Year]
		UserDefinedText,//4.2.2   TXXX[#TXXX User defined text information frame]
		UniqueFileIdentifier,//4.1     UFID[#sec4.1 Unique file identifier]
		TermsOfUse,//4.23    USER[#sec4.23 Terms of use]
		UnsychronizedLyric,//4.9     USLT[#sec4.9 Unsychronized lyric / text transcription]
		CommercialInformation,//4.3.1   WCOM[#WCOM Commercial information]
		CopyrightLegalInformation,//4.3.1   WCOP[#WCOP Copyright / Legal information]
		OfficialAudioFileWebpage,//4.3.1   WOAF[#WOAF Official audio file webpage]
		OfficialArtistPerformerWebpage,//4.3.1   WOAR[#WOAR Official artist / performer webpage]
		OfficialAudioSourceWebpage,//4.3.1   WOAS[#WOAS Official audio source webpage]
		InternetRadioStationHomepage,//4.3.1   WORS[#WORS Official internet radio station homepage]
		Payment,//4.3.1   WPAY[#WPAY Payment]
		PublishersOfficialWebpage,//4.3.1   WPUB[#WPUB Publishers official webpage]
		UserDefinedURLLinkFrame//4.3.2   WXXX[#WXXX User defined URL link frame]
	}
	ID3v2xFrameTag;



	typedef struct ID3_
	{
		// Version 1.0
		wchar_t Title[ID3TitleSize + 1];
		wchar_t Artist[ID3ArtistSize + 1];
		wchar_t Album[ID3AlbumSize + 1];
		wchar_t Year[ID3YearSize + 1];
		wchar_t Comment[ID3CommentSize + 1];
		unsigned char Genre;

		// Version 1.1
		unsigned char TrackID;

		// Version 2.x
		unsigned int BeatsPerMinute;
		wchar_t Composer[ID3ArtistSize + 1];
	}
	ID3;

	PXPublic ID3v2xFrameTag ConvertID3v2xFrameTag(const unsigned int id3v2xFrameTagID);

	PXPublic PXActionResult ID3Parse(ID3* const id3, PXDataStream* const pxDataStream);

#ifdef __cplusplus
}
#endif

#endif