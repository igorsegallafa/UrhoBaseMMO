#include "stdafx.h"
#include "INIParser.h"

namespace INI
{
Parser::Parser( Context * pcContext, BOOL bCaseSensitive ) : Resource( pcContext ), bCaseSensitive( bCaseSensitive )
{
}

Parser::~Parser()
{
}

void Parser::RegisterObject( Context * pcContext )
{
	pcContext->RegisterFactory<INI::Parser>();
}

bool Parser::BeginLoad( Deserializer& source )
{
	unsigned int iDataSize = source.GetSize();

	if( !iDataSize && !source.GetName().Empty() )
		return false;

	ConfigSection* configSection = new ConfigSection();
	vConfigMap.Push( *configSection );

	while( !source.IsEof() )
	{
		// Reads the next line
		auto line = source.ReadLine();

		// Parse headers
		if( line.StartsWith( "[" ) && line.EndsWith( "]" ) )
		{
			//String sectionName = line.Substring(1, line.Length() - 2);
			//currentMap = &_configMap[sectionName];

			vConfigMap.Push( ConfigSection() );
			configSection = &vConfigMap.Back();

		}

		configSection->Push( line );
	}

	return true;
}

bool Parser::Save( Serializer& dest ) const
{
	dest.WriteLine( "################" );
	dest.WriteLine( "# AUTO-GENERATED" );
	dest.WriteLine( "################" );

	// Iterate over all sections, printing out the header followed by the properties
	for( auto itr = vConfigMap.Begin(); itr != vConfigMap.End(); itr++ )
	{
		if( itr->Begin() == itr->End() )
			continue;

		// Don't print section if there's nothing to print
		bool hasHeader = false;
		for( auto section_itr = itr->Begin(); section_itr != itr->End(); section_itr++ )
		{
			if( ParseComments( *section_itr ) != String::EMPTY )
			{
				hasHeader = true;
				dest.WriteLine( "" );
				break;
			}
		}

		auto section_itr = itr->Begin();

		// Doesn't print header if it's empty
		if( hasHeader )
		{
			dest.WriteLine( "[" + ParseHeader( *section_itr ) + "]" );
			dest.WriteLine( "" );
		}

		for( ; section_itr != itr->End(); section_itr++ )
		{
			auto line = ParseComments( *section_itr );

			String property;
			String value;

			ParseProperty( line, property, value );

			if( property != String::EMPTY && value != String::EMPTY )
				dest.WriteLine( property + "=" + value );
		}
	}

	return true;
}

bool Parser::Save( Serializer& dest, bool smartSave ) const
{
	if( !smartSave )
		return Save( dest );

	// Iterate over all sections, printing out the header followed by the properties
	for( auto itr = vConfigMap.Begin(); itr != vConfigMap.End(); itr++ )
	{
		if( itr->Begin() == itr->End() )
			continue;

		for( auto section_itr = itr->Begin(); section_itr != itr->End(); section_itr++ )
		{
			auto line = *section_itr;

			dest.WriteLine( line );
		}
	}

	return true;
}

BOOL Parser::FromString( const String & strSource )
{
	if( strSource.Empty() )
		return false;

	MemoryBuffer buffer( strSource.CString(), strSource.Length() );
	return Load( buffer );
}

BOOL Parser::Has( const String & strSection, const String & strParameter )
{
	return GetString( strSection, strParameter ) != String::EMPTY;
}

const String Parser::GetString( const String & strSection, const String & strParameter, const String & strDefaultValue )
{
	// Find the correct section
	ConfigSection* configSection = 0;
	for( auto itr = vConfigMap.Begin(); itr != vConfigMap.End(); itr++ )
	{
		if( itr->Begin() == itr->End() )
			continue;

		auto header = *(itr->Begin());
		header = ParseHeader( header );

		if( bCaseSensitive )
		{
			if( strSection == header )
			{
				configSection = &(*itr);
			}
		}
		else
		{
			if( strSection.ToLower() == header.ToLower() )
			{
				configSection = &(*itr);
			}
		}
	}

	// Section doesn't exist
	if( !configSection )
		return strDefaultValue;

	for( auto itr = configSection->Begin(); itr != configSection->End(); itr++ )
	{
		String property;
		String value;
		ParseProperty( *itr, property, value );

		if( property == String::EMPTY || value == String::EMPTY )
			continue;

		if( bCaseSensitive )
		{
			if( strParameter == property )
				return value;
		}
		else
		{
			if( strParameter.ToLower() == property.ToLower() )
				return value;
		}
	}

	return strDefaultValue;
}

const int Parser::GetInt( const String & strSection, const String & strParameter, const int iDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return iDefaultValue;

	return ToInt( property );
}

const BOOL Parser::GetBool( const String & strSection, const String & strParameter, const BOOL bDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return bDefaultValue;

	return ToBool( property );
}

const float Parser::GetFloat( const String & strSection, const String & strParameter, const float fDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return fDefaultValue;

	return ToFloat( property );
}

const Vector2 Parser::GetVector2( const String & strSection, const String & strParameter, const Vector2 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToVector2( property );
}

const Vector3 Parser::GetVector3( const String & strSection, const String & strParameter, const Vector3 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToVector3( property );
}

const Vector4 Parser::GetVector4( const String & strSection, const String & strParameter, const Vector4 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToVector4( property );
}

const Quaternion Parser::GetQuaternion( const String & strSection, const String & strParameter, const Quaternion & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToQuaternion( property );
}

const Color Parser::GetColor( const String & strSection, const String & strParameter, const Color & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToColor( property );
}

const IntRect Parser::GetIntRect( const String & strSection, const String & strParameter, const IntRect & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToIntRect( property );
}

const IntVector2 Parser::GetIntVector2( const String & strSection, const String & strParameter, const IntVector2 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToIntVector2( property );
}

const Matrix3 Parser::GetMatrix3( const String & strSection, const String & strParameter, const Matrix3 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToMatrix3( property );
}

const Matrix3x4 Parser::GetMatrix3x4( const String & strSection, const String & strParameter, const Matrix3x4 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToMatrix3x4( property );
}

const Matrix4 Parser::GetMatrix4( const String & strSection, const String & strParameter, const Matrix4 & cDefaultValue )
{
	auto property = GetString( strSection, strParameter );

	if( property == String::EMPTY )
		return cDefaultValue;

	return ToMatrix4( property );
}

void Parser::Set( const String & strSection, const String & strParameter, const String & strValue )
{
	// Find the correct section
	ConfigSection* configSection = 0;
	for( auto itr = vConfigMap.Begin(); itr != vConfigMap.End(); itr++ )
	{
		if( itr->Begin() == itr->End() )
			continue;

		auto header = *(itr->Begin());
		header = ParseHeader( header );

		if( bCaseSensitive )
		{
			if( strSection == header )
			{
				configSection = &(*itr);
			}
		}
		else
		{
			if( strSection.ToLower() == header.ToLower() )
			{
				configSection = &(*itr);
			}
		}
	}

	// Section doesn't exist
	if( !configSection )
	{
		// Create section
		vConfigMap.Push( ConfigSection() );
		configSection = &vConfigMap.Back();
	}

	String* line = 0;
	unsigned separatorPos = 0;
	for( auto itr = configSection->Begin(); itr != configSection->End(); itr++ )
	{
		// Find property seperator
		separatorPos = itr->Find( "=" );
		if( separatorPos == String::NPOS )
		{
			separatorPos = itr->Find( ":" );
		}

		// Not a property
		if( separatorPos == String::NPOS )
			continue;

		String workingLine = ParseComments( *itr );

		auto oldParameter = workingLine.Substring( 0, separatorPos ).Trimmed();
		auto oldValue = workingLine.Substring( separatorPos + 1 ).Trimmed();

		// Not the correct parameter
		if( bCaseSensitive ? (oldParameter == strParameter) : (oldParameter.ToLower() == strParameter.ToLower()) )
		{
			// Replace the value

			itr->Replace( itr->Find( oldValue, separatorPos ), oldValue.Length(), strValue );
			return;
		}
	}

	// Parameter doesn't exist yet
	// We need to find a good place to insert the parameter
	// Avoiding lines which are entirely comments or whitespacing
	int index = configSection->Size() - 1;
	for( int i = index; i >= 0; i-- )
	{
		if( ParseComments( (*configSection)[i] ) != String::EMPTY )
		{
			index = i + 1;
			break;
		}
	}
	configSection->Insert( index, strParameter + "=" + strValue );
}

// Returns header without bracket
String Parser::ParseHeader( String line ) const
{
	// Only parse comments outside of headers
	unsigned commentPos = 0;

	while( commentPos != String::NPOS )
	{
		// Find next comment
		auto lastCommentPos = commentPos;
		auto commaPos = line.Find( "//", commentPos );
		auto hashPos = line.Find( "#", commentPos );
		commentPos = (commaPos < hashPos) ? commaPos : hashPos;

		// Header is behind a comment
		if( line.Find( "[", lastCommentPos ) > commentPos )
		{
			// Stop parsing this line
			break;
		}

		// Header is before the comment
		if( line.Find( "[" ) < commentPos )
		{
			int startPos = line.Find( "[" ) + 1;
			int l1 = line.Find( "]" );
			int length = l1 - startPos;
			line = line.Substring( startPos, length );
			break;
		}
	}

	line = line.Trimmed();

	return line;
}

//  property or Empty if no property
void Parser::ParseProperty( String line, String& property, String& value ) const
{
	line = ParseComments( line );

	// Find property seperator
	auto separatorPos = line.Find( "=" );
	if( separatorPos == String::NPOS )
	{
		separatorPos = line.Find( ":" );
	}

	// Not a property
	if( separatorPos == String::NPOS )
	{
		property = String::EMPTY;
		value = String::EMPTY;
		return;
	}

	property = line.Substring( 0, separatorPos ).Trimmed();
	value = line.Substring( separatorPos + 1 ).Trimmed();
}

// strips comments and whitespaces
String Parser::ParseComments( String line ) const
{
	// Comments are normalized
	line.Replace( "//", "#" );

	// Ignore comments
	unsigned commentPos = line.Find( "#" );
	if( commentPos != String::NPOS )
	{
		line = line.Substring( 0, commentPos );
	}

	return line;
}
}