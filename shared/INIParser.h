#pragma once

namespace INI
{
typedef Vector<String> ConfigSection;
typedef Vector<ConfigSection> ConfigMap;

class Parser : public Resource
{
public:
	//Construtor
								Parser( Context * pcContext, BOOL bCaseSensitive = FALSE );
							   ~Parser();

	static void					RegisterObject( Context * pcContext );

	void						SetCaseSensitive( BOOL bCaseSensitive_ ){ bCaseSensitive = bCaseSensitive_; }

	//Funções do Resource
	virtual bool				BeginLoad( Deserializer & source );
	virtual bool				Save( Serializer & dest) const;
	virtual bool				Save( Serializer & dest, bool smartSave ) const;

	//Desiarilizar uma String
	BOOL						FromString( const String & strSource );

	const ConfigMap			  * GetMap(){ return &vConfigMap; }

	BOOL						Has( const String & strSection, const String & parameter );

	const String				GetString( const String & strSection, const String & strParameter, const String & strDefaultValue = String::EMPTY );
	const int					GetInt( const String & strSection, const String & strParameter, const int iDefaultValue = 0 );
	const BOOL					GetBool( const String & strSection, const String & strParameter, const BOOL bDefaultValue = FALSE );
	const float					GetFloat( const String & strSection, const String & strParameter, const float fDefaultValue = 0.f );
	const Vector2				GetVector2( const String & strSection, const String & strParameter, const Vector2 & cDefaultValue = Vector2::ZERO );
	const Vector3				GetVector3( const String & strSection, const String & strParameter, const Vector3 & cDefaultValue = Vector3::ZERO );
	const Vector4				GetVector4( const String & strSection, const String & strParameter, const Vector4 & cDefaultValue = Vector4::ZERO );
	const Quaternion			GetQuaternion( const String & strSection, const String & strParameter, const Quaternion & cDefaultValue = Quaternion::IDENTITY );
	const Color					GetColor( const String & strSection, const String & strParameter, const Color & cDefaultValue = Color::WHITE );
	const IntRect				GetIntRect( const String & strSection, const String & strParameter, const IntRect & cDefaultValue = IntRect::ZERO );
	const IntVector2			GetIntVector2( const String & strSection, const String & strParameter, const IntVector2 & cDefaultValue = IntVector2::ZERO );
	const Matrix3				GetMatrix3( const String & strSection, const String & strParameter, const Matrix3 & cDefaultValue = Matrix3::IDENTITY );
	const Matrix3x4				GetMatrix3x4( const String & strSection, const String & strParameter, const Matrix3x4 & cDefaultValue = Matrix3x4::IDENTITY );
	const Matrix4				GetMatrix4( const String & strSection, const String & strParameter, const Matrix4 & cDefaultValue = Matrix4::IDENTITY );
		
	void						Set( const String & strSection, const String & strParameter, const String & strValue );

protected:
	String						ParseHeader( String strLine ) const;
	void						ParseProperty( String strLine, String & strProperty, String & strValue ) const;
	String						ParseComments( String strLine ) const;
protected:
	BOOL						bCaseSensitive;
	ConfigMap					vConfigMap;
};
}