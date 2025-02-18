#include "PXCompiler.h"

#include <stdio.h>

#include <File/PXDataStream.h>
#include <Media/PXText.h>
#include <Math/PXMath.h>

#define PXCompilerSanitise 1

void PXCompilerSettingsConstruct(PXCompilerSettings* const compilerSettings)
{
	MemoryClear(compilerSettings, sizeof(PXCompilerSettings));
}

void PXCompilerSymbolEntryAdd(PXDataStream* const dataStream, const PXCompilerSymbolEntry* const compilerSymbolEntry)
{
	const unsigned char symbolID = compilerSymbolEntry->ID;

	PXDataStreamWriteI8U(dataStream, symbolID);
	PXDataStreamWriteI32U(dataStream, compilerSymbolEntry->Coloum);
	PXDataStreamWriteI32U(dataStream, compilerSymbolEntry->Line);
	PXDataStreamWriteI32U(dataStream, compilerSymbolEntry->Size);
	PXDataStreamWriteB(dataStream, &compilerSymbolEntry->Source, sizeof(void*));


#if 0

	PXSize idBufferSize = 10;
	char idbuffer[15];
	PXSize textBufferSize = 20;
	char textbuffer[25];

	MemoryClear(idbuffer, sizeof(idbuffer));
	MemoryClear(textbuffer, sizeof(textbuffer));

	switch (compilerSymbolEntry->ID)
	{
		case PXCompilerSymbolLexerQuestionmark:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("?", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerExclamation:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("!", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerDot:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA(".", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerComma:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA(",", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerColon:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA(":", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerSemiColon:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA(";", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerPlus:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("+", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerMinus:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("-", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerSlash:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("/", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerAsterisk:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("*", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerSlashBack:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("\\", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerAmpercant:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("&", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerPercent:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("%", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBar:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("|", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerHash:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("#", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerDegree:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("�", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerExponent:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("^", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerTilde:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("~", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerApostrophe:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("\'", 1, textbuffer, textBufferSize);
			break;
		}

		case PXCompilerSymbolLexerBrackedRoundOpen:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("(", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBrackedRoundClose:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA(")", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBracketSquareOpen:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("[", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBracketSquareClose:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("]", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBracketCurlyOpen:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("{", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBracketCurlyClose:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("}", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBracketAngleOpen:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA("<", 1, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerBracketAngleClose:
		{
			PXTextCopyA("*Symbol*", 9, idbuffer, idBufferSize);
			PXTextCopyA(">", 1, textbuffer, textBufferSize);
			break;
		}

		case PXCompilerSymbolLexerWhiteSpace:
		{
			PXTextCopyA("***Whitespace***", 17, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerNewLine:
		{
			PXTextCopyA("\\n", 3, idbuffer, idBufferSize);
			PXTextCopyA("***New Line***", 15, textbuffer, textBufferSize);
			break;
		}
		case PXCompilerSymbolLexerComment:
			PXTextCopyA("comment", 8, idbuffer, idBufferSize);
			PXTextCopyA(compilerSymbolEntry->Source, compilerSymbolEntry->Size, textbuffer, textBufferSize);
			break;

		case PXCompilerSymbolLexerBool:
			PXTextCopyA("bool", 5, idbuffer, idBufferSize);
			sprintf(textbuffer, "%s", compilerSymbolEntry->DataC ? "true" : "false");
			break;

		case PXCompilerSymbolLexerFloat:
			PXTextCopyA("float", 6, idbuffer, idBufferSize);
			sprintf(textbuffer, "%f", compilerSymbolEntry->DataF);
			break;

		case PXCompilerSymbolLexerInteger:
			PXTextCopyA("int", 4, idbuffer, idBufferSize);
			sprintf(textbuffer, "%i", compilerSymbolEntry->DataI);
			break;

		case PXCompilerSymbolLexerString:
			PXTextCopyA("string", 7, idbuffer, idBufferSize);
			PXTextCopyA(compilerSymbolEntry->Source, compilerSymbolEntry->Size, textbuffer, textBufferSize);
			break;

		case PXCompilerSymbolLexerGenericElement:
		{
			//PXTextCopyA("*Generic*", 10, idbuffer, idBufferSize);
			PXTextCopyA(compilerSymbolEntry->Source, compilerSymbolEntry->Size, textbuffer, textBufferSize);
			break;
		}
	}


	printf
	(
		"|| C:%-3i L:%-3i S:%-3i | %-10s -> %-20s ||\n",
		compilerSymbolEntry->Coloum,
		compilerSymbolEntry->Line,
		compilerSymbolEntry->Size,
		idbuffer,
		textbuffer
	);
#endif
}

void PXCompilerSymbolEntryExtract(PXDataStream* const dataStream, PXCompilerSymbolEntry* compilerSymbolEntry)
{
	void* const oldPos = PXDataStreamCursorPosition(dataStream);
	PXSize size = 0;

	unsigned char symbolID = 0;

	size += PXDataStreamReadI8U(dataStream, &symbolID);
	size += PXDataStreamReadI32U(dataStream, &compilerSymbolEntry->Coloum);
	size += PXDataStreamReadI32U(dataStream, &compilerSymbolEntry->Line);
	size += PXDataStreamReadI32U(dataStream, &compilerSymbolEntry->Size);
	size += PXDataStreamReadB(dataStream, &compilerSymbolEntry->Source, sizeof(void*));

	compilerSymbolEntry->ID = symbolID;

#if PXCompilerSanitise
	MemorySet(oldPos, '#', size);
#endif
}

void PXCompilerSymbolEntryPeek(PXDataStream* const dataStream, PXCompilerSymbolEntry* compilerSymbolEntry)
{
	void* const oldPos = PXDataStreamCursorPosition(dataStream);
	PXSize size = 0;

	unsigned char symbolID = 0;

	size += PXDataStreamReadI8U(dataStream, &symbolID);
	size += PXDataStreamReadI32U(dataStream, &compilerSymbolEntry->Coloum);
	size += PXDataStreamReadI32U(dataStream, &compilerSymbolEntry->Line);
	size += PXDataStreamReadI32U(dataStream, &compilerSymbolEntry->Size);
	size += PXDataStreamReadB(dataStream, &compilerSymbolEntry->Source, sizeof(void*));

	compilerSymbolEntry->ID = symbolID;

	PXDataStreamCursorRewind(dataStream, size);
}

PXCompilerSymbolLexer PXCompilerTryAnalyseType(const char* const text, const PXSize textSize, PXCompilerSymbolEntry* const compilerSymbolEntry)
{
	switch (textSize == 1)
	{
		case '.': return PXCompilerSymbolLexerDot;
		case ',': return PXCompilerSymbolLexerComma;
		case ':': return PXCompilerSymbolLexerColon;
		case ';': return PXCompilerSymbolLexerSemiColon;
		case '?': return PXCompilerSymbolLexerQuestionmark;
		case '!': return PXCompilerSymbolLexerExclamation;
		case '#': return PXCompilerSymbolLexerHash;
		case '+': return PXCompilerSymbolLexerPlus;
		case '-': return PXCompilerSymbolLexerMinus;
		case '/': return PXCompilerSymbolLexerSlash;
		case '*': return PXCompilerSymbolLexerAsterisk;
		case '\\': return PXCompilerSymbolLexerSlashBack;
		case '&': return PXCompilerSymbolLexerAmpercant;
		case '%': return PXCompilerSymbolLexerPercent;
		case '|': return PXCompilerSymbolLexerBar;
		case '�': return PXCompilerSymbolLexerDegree;
		case '^': return PXCompilerSymbolLexerExponent;
		case '~': return PXCompilerSymbolLexerTilde;
		case '\'': return PXCompilerSymbolLexerApostrophe;
	}

	switch (text[0])
	{
		case '\r':
		case '\n':
			return PXCompilerSymbolLexerNewLine;

		case ' ':
		case '\t':
		{
			return PXCompilerSymbolLexerWhiteSpace;
		}

		case '.': 
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerDot; 
		}
		case ',': 
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerComma; 
		}
		case ':': 
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerColon; 
		}
		case ';': 
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerSemiColon; 
		}

		case '?': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerQuestionmark; }
		case '!': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerExclamation; }
		case '*': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerAsterisk; }
		case '&': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerAmpercant; }
		case '%': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerPercent; }
		case '|': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerBar; }
		case '�': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerDegree; }
		case '^': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerExponent; }
		case '~': {compilerSymbolEntry->Size = 1; return PXCompilerSymbolLexerTilde; }

		case '=':
		{
			if (text[1] == '=')
			{
				if (text[2] == '=')
				{
					compilerSymbolEntry->Size = 3;

					return PXCompilerSymbolLexerEqualTrippel;
				}

				compilerSymbolEntry->Size = 2;

				return PXCompilerSymbolLexerEqualDouble;
			}

			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerEqual;
		}

		case '{':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBracketCurlyOpen;
		}
		case '}':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBracketCurlyClose;
		}
		case '(':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBrackedRoundOpen;
		}
		case ')':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBrackedRoundClose;
		}
		case '[':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBracketSquareOpen;
		}
		case ']':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBracketSquareClose;
		}
		case '#':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerHash;
		}
		case '>':
		{
			if (text[1] == '=')
			{
				compilerSymbolEntry->Size = 2;

				return PXCompilerSymbolLexerBiggerAndEqual;
			}

			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBracketAngleClose;
		}
		case '<':
		{
			if (text[1] == '=')
			{
				if (text[2] == '>')
				{
					compilerSymbolEntry->Size = 3;

					return PXCompilerSymbolLexerCompareThreeWay;
				}

				compilerSymbolEntry->Size = 2;

				return PXCompilerSymbolLexerSmalerAndEqual;
			}

			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerBracketAngleOpen;
		}
		case '/':
		{
			compilerSymbolEntry->Size = 1;

			return PXCompilerSymbolLexerSlash;
		}
		case '\'':
		{
			const PXBool isFull = text[textSize - 1] == '\'';

			if (!isFull)
			{
				const PXSize symbolPositionQuotationMark = PXTextFindFirstCharacterA(compilerSymbolEntry->Source, compilerSymbolEntry->Size, '\'');
				const PXBool hasIndex = symbolPositionQuotationMark != (PXSize)-1;

				if (!hasIndex)
				{
					// Error
				}

				compilerSymbolEntry->Size = symbolPositionQuotationMark;
			}

			return PXCompilerSymbolLexerString;
		}
		case '\"':
		{
			const PXBool isFull = text[textSize - 1] == '\"';

			if (!isFull)
			{
				const PXSize symbolPositionQuotationMark = PXTextFindFirstCharacterA(compilerSymbolEntry->Source, compilerSymbolEntry->Size, '\"');
				const PXBool hasIndex = symbolPositionQuotationMark != (PXSize)-1;

				if (!hasIndex)
				{
					// Error
				}

				compilerSymbolEntry->Size = symbolPositionQuotationMark;
			}

			return PXCompilerSymbolLexerString;
		}
		case 'T':
		case 't':
		{
			const PXBool  result = PXTextCompareIgnoreCaseA(text, textSize, "true", 4) && textSize > 4;

			if (result)
			{
				compilerSymbolEntry->DataC = PXYes;

				return PXCompilerSymbolLexerBool;
			}

			break;
		}
		case 'F':
		case 'f':
		{
			const PXBool  result = PXTextCompareIgnoreCaseA(text, textSize, "false", 5) && textSize > 5;

			if (result)
			{
				compilerSymbolEntry->DataC = PXNo;

				return PXCompilerSymbolLexerBool;
			}

			break;
		}
		case '+':
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			// Probe for number
			const PXSize dotIndex = PXTextFindFirstCharacterA(text, textSize, '.');
			const PXBool probablyFloat = dotIndex != (PXSize)-1;
			PXSize writtenNumbers = 0;

			PXBool isValidFloatSyntax = PXTrue;

			if (probablyFloat)
			{
				for (PXSize i = 0; (i <= dotIndex +1) && isValidFloatSyntax; i++)
				{
					isValidFloatSyntax = PXTextFloatIsAllowedCharacter(text[i]);
				}
			}

			if (probablyFloat && isValidFloatSyntax)
			{
				float value = 0;

				const PXSize writtenNumbers = PXTextToFloatA(text, textSize, &value);
				const PXBool isFloat = textSize == writtenNumbers;

				if (isFloat)
				{
					compilerSymbolEntry->Source = 0;
					compilerSymbolEntry->Size = writtenNumbers;
					compilerSymbolEntry->DataF = value;

					return PXCompilerSymbolLexerFloat;
				}
			}
			else
			{
				unsigned int value = 0;

				const PXSize writtenNumbers = PXTextToIntA(text, textSize, &value);	

				if (writtenNumbers > 0)
				{
					compilerSymbolEntry->Source = 0;
					compilerSymbolEntry->Size = writtenNumbers;
					compilerSymbolEntry->DataI = value;

					return PXCompilerSymbolLexerInteger;
				}			
			}
		}
	}

	// Before we end, check if we can cleave internal stuff mixed into the block

	PXSize i = compilerSymbolEntry->Size;
	PXSize newSize = 0;

	for (i = 0; i < compilerSymbolEntry->Size; ++i)
	{
		const char symbol = compilerSymbolEntry->Source[i];
		const PXBool isNumber = ('A' <= symbol && symbol <= 'Z') || ('a' <= symbol && symbol <= 'z') || symbol == '.' || symbol == '_';

		newSize += isNumber;

		if (!isNumber)
		{
			break;
		}
	}

	compilerSymbolEntry->Size = newSize;

	return PXCompilerSymbolLexerGenericElement;
}

void PXCompilerLexicalAnalysis(PXDataStream* const inputStream, PXDataStream* const outputStream, const PXCompilerSettings* const compilerSettings)
{
	PXSize currentLine = 0;
	PXSize currentColoum = 0;
	PXBool isFirstWhiteSpaceInLine = 1u;

#if PXCompilerSanitise
	MemorySet(outputStream->Data, '#', outputStream->DataSize);
#endif

	const PXCompilerSymbolLexer newLineSymbol = compilerSettings->IntrepredNewLineAsWhiteSpace ? PXCompilerSymbolLexerWhiteSpace : PXCompilerSymbolLexerNewLine;

	while (!PXDataStreamIsAtEnd(inputStream))
	{
		PXCompilerSymbolEntry compilerSymbolEntry;
		compilerSymbolEntry.Source = (const char*)PXDataStreamCursorPosition(inputStream);

		//-----------------------------------------------------------------------------
		// Consume whitespace
		//-----------------------------------------------------------------------------
		{
			const PXSize whiteSpaceSize = PXDataStreamSkipEmptySpace(inputStream); // Skip 'space' and TABs

			currentColoum += whiteSpaceSize;

			if (whiteSpaceSize)
			{
				isFirstWhiteSpaceInLine = 0;

				compilerSymbolEntry.ID = PXCompilerSymbolLexerWhiteSpace;
				compilerSymbolEntry.Line = currentLine;
				compilerSymbolEntry.Coloum = currentColoum;
				compilerSymbolEntry.Size = whiteSpaceSize;

				if (compilerSettings->KeepWhiteSpace && isFirstWhiteSpaceInLine)
				{
					PXCompilerSymbolEntryAdd(outputStream, &compilerSymbolEntry);
				}

				continue;
			}
		}

		//-----------------------------------------------------------------------------
		// Consume new line
		//-----------------------------------------------------------------------------
		{
			const PXSize endofLineSize = PXDataStreamSkipEndOfLineCharacters(inputStream);

			if (endofLineSize)
			{
				const PXSize linesSkipped = PXTextCountA(compilerSymbolEntry.Source, endofLineSize, '\n');

				compilerSymbolEntry.ID = newLineSymbol;
				compilerSymbolEntry.Line = currentLine;
				compilerSymbolEntry.Coloum = currentColoum;
				compilerSymbolEntry.Size = endofLineSize;

				isFirstWhiteSpaceInLine = 1u;

				currentColoum = 0; // Reset, next entry will begin in new line
				currentLine += linesSkipped;

				if (compilerSettings->KeepNewLines)
				{
					PXCompilerSymbolEntryAdd(outputStream, &compilerSymbolEntry);
				}	

				continue;
			}
		}
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		// Extract comments, Single line and multible lines
		//-----------------------------------------------------------------------------
		{
			const PXBool isLineComment = PXTextCompareA(compilerSymbolEntry.Source, compilerSettings->CommentSingleLineSize, compilerSettings->CommentSingleLine, compilerSettings->CommentSingleLineSize);

			if (isLineComment)
			{
				compilerSymbolEntry.ID = PXCompilerSymbolLexerComment; // This is a comment 
				compilerSymbolEntry.Source += compilerSettings->CommentSingleLineSize;
				compilerSymbolEntry.Size -= compilerSettings->CommentSingleLineSize;
				compilerSymbolEntry.Size += PXDataStreamSkipLine(inputStream);

				if (compilerSettings->CommentsKeep)
				{
					PXCompilerSymbolEntryAdd(outputStream, &compilerSymbolEntry);
				}

				continue;
			}

			const PXBool isStartOfMultibleLineComment = PXTextCompareA(compilerSymbolEntry.Source, compilerSymbolEntry.Size, compilerSettings->CommentMultibleLineBegin, compilerSettings->CommentMultibleLineBeginSize);

			if (isStartOfMultibleLineComment)
			{
				const PXSize index = PXTextFindFirstStringA(compilerSymbolEntry.Source, compilerSymbolEntry.Size, compilerSettings->CommentMultibleLineEnd, compilerSettings->CommentMultibleLineEndSize);
				const PXBool isCompleate = index != -1;

				if (!isCompleate)
				{
					// Error, we have a multiline comment without an end.
					printf("Errr\n");
				}

				compilerSymbolEntry.ID = PXCompilerSymbolLexerComment;
				compilerSymbolEntry.Source += compilerSettings->CommentMultibleLineEndSize;
				compilerSymbolEntry.Size -= compilerSettings->CommentMultibleLineEndSize;
				compilerSymbolEntry.Size += index;

				if (compilerSettings->CommentsKeep)
				{
					PXCompilerSymbolEntryAdd(outputStream, &compilerSymbolEntry);
				}

				continue;
			}
		}
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		// Consume block
		//-----------------------------------------------------------------------------
		{
			PXSize fullBlockSize = PXDataStreamSkipBlock(inputStream);	// consume block
			char* blockStart = compilerSymbolEntry.Source;

			while (fullBlockSize > 0)
			{
				compilerSymbolEntry.Source = blockStart;
				compilerSymbolEntry.Line = currentLine;
				compilerSymbolEntry.Coloum = currentColoum;
				compilerSymbolEntry.Size = fullBlockSize;
				compilerSymbolEntry.ID = PXCompilerTryAnalyseType(compilerSymbolEntry.Source, compilerSymbolEntry.Size, &compilerSymbolEntry);

				if (compilerSymbolEntry.ID == PXCompilerSymbolLexerWhiteSpace || compilerSymbolEntry.ID == PXCompilerSymbolLexerNewLine)
				{
					break;
				}

				if (compilerSymbolEntry.ID == PXCompilerSymbolLexerString)
				{
					++compilerSymbolEntry.Source;
					compilerSymbolEntry.Size -= 2;
				}

				PXCompilerSymbolEntryAdd(outputStream, &compilerSymbolEntry);

				if (compilerSymbolEntry.ID == PXCompilerSymbolLexerString)
				{
					--compilerSymbolEntry.Source;
					compilerSymbolEntry.Size += 2;
				}

				// Change data for next itteration
				blockStart += compilerSymbolEntry.Size; // Move data point forward
				fullBlockSize -= compilerSymbolEntry.Size; // Reduce blocksize by scanned data
				currentColoum += compilerSymbolEntry.Size; // Forward the coloum of the data position			
			}
		}
	}
}

PXBool PXCompilerParseStringUntilNewLine(PXDataStream* const inputStream, char* const text, const PXSize textMaxSize, PXSize* const textSize)
{
	PXCompilerSymbolEntry compilerSymbolEntry;

	PXCompilerSymbolEntryExtract(inputStream, &compilerSymbolEntry); // Expect a name.

	const PXBool isText = PXCompilerSymbolLexerGenericElement == compilerSymbolEntry.ID;

	if (!isText)
	{
		return PXNo;
	}

	PXInt16U line = compilerSymbolEntry.Line;
	PXInt16U coloumStart = compilerSymbolEntry.Coloum;
	PXSize dataBlockSize = compilerSymbolEntry.Size;
	char* dataBlockPoint = compilerSymbolEntry.Source;

	while (1u)
	{
		PXCompilerSymbolEntryPeek(inputStream, &compilerSymbolEntry);

		const PXBool isDone = (compilerSymbolEntry.Line != line) || (compilerSymbolEntry.ID == PXCompilerSymbolLexerNewLine);

		if (isDone)
		{
			break;
		}

		PXCompilerSymbolEntryExtract(inputStream, &compilerSymbolEntry);

		dataBlockSize = (compilerSymbolEntry.Coloum - coloumStart) + compilerSymbolEntry.Size;
	}

	*textSize = PXTextCopyA(dataBlockPoint, dataBlockSize, text, textMaxSize);

	return PXYes;
}

PXBool PXCompilerParseIntUnsignedSingle(PXDataStream* const inputStream, PXCompilerSymbolEntry* const compilerSymbolEntry, unsigned int* const value)
{
	PXCompilerSymbolEntryExtract(inputStream, compilerSymbolEntry);

	const PXBool isInt = compilerSymbolEntry->ID == PXCompilerSymbolLexerInteger;

	*value = compilerSymbolEntry->DataI;

	return isInt;
}

PXBool PXCompilerParseFloatSingle(PXDataStream* const inputStream, float* const values)
{
	PXCompilerSymbolEntry compilerSymbolEntry;

	PXCompilerSymbolEntryPeek(inputStream, &compilerSymbolEntry);

	const PXBool isFloat = compilerSymbolEntry.ID == PXCompilerSymbolLexerFloat;

	if (isFloat)
	{
		*values = compilerSymbolEntry.DataF;

		PXCompilerSymbolEntryExtract(inputStream, &compilerSymbolEntry);
	}

	return isFloat;
}

PXBool PXCompilerParseFloatList(PXDataStream* const inputStream, float* const values, const PXSize valuesMaxSize, PXSize* const valuesSize)
{
	for (PXSize i = 0; i < valuesMaxSize; ++i)
	{
		const PXBool isFloat = PXCompilerParseFloatSingle(inputStream, &values[*valuesSize]);

		if (!isFloat)
		{
			// we are at the line end

			return PXNo; // finished
		}

		++(*valuesSize);
	}

	return PXYes;
}
