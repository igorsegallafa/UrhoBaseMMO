#pragma once

#include "DatabaseSubArray.h"

namespace Database
{
class Key
{
public:
	//Constructor
												Key(){}
												Key( const std::string & strName ) : strKeyName( strName ){}
												Key( const Key & sKey ) : strKeyName( sKey.strKeyName ){}

	template <class T>
												Key( const std::string & strName, const T && t ) : strKeyName( strName ){ cDocumentation.doc = make_document( kvp( strKeyName, t )); }
												Key( const std::string & strName, const SubArray && sSubArray ) : strKeyName( strName ){ cDocumentation.doc = make_document( kvp( strKeyName, sSubArray.View() )); }


	/**
	 * @return A Builded Concatenated Documentation.
	 */
	inline bsoncxx::builder::concatenate_doc	Documentation() const{ return cDocumentation; }

	/**
	 * Create a document to '$exists' MongoDB operator.
	 * @param bValue Boolean value used to '$exists' operator = TRUE by default.
	 * @return A Builded Concatenated Documentation specifically to this operator.
	 */
	Key										  & Exists( BOOL bValue = TRUE )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$exists", bValue ) ) ) );
		return *this;
	}

	/**
	 * Use operator '==' to create a document with '$eq' MongoDB operator.
	 * @param t Custom value to pair with current Key.
	 * @return A Key with Builded Documentation.
	 */
	template <class T>
	Key & operator == ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$eq", t ) ) ) );
		return *this;
	}

	/**
	 * Use operator '!=' to create a document with '$ne' MongoDB operator.
	 * @param t Custom value to pair with current Key.
	 * @return A Key with Builded Documentation.
	 */
	template <class T>
	Key & operator != ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$ne", t ) ) ) );
		return *this;
	}

	/**
	 * Use operator '<=' to create a document with '$lte' MongoDB operator.
	 * @param t Custom value to pair with current Key.
	 * @return A Key with Builded Documentation.
	 */
	template <class T>
	Key & operator <= ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$lte", t ) ) ) );
		return *this;
	}

	/**
	 * Use operator '<' to create a document with '$lt' MongoDB operator.
	 * @param t Custom value to pair with current Key.
	 * @return A Key with Builded Documentation.
	 */
	template <class T>
	Key & operator < ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$lt", t ) ) ) );
		return *this;
	}

	/**
	 * Use operator '>=' to create a document with '$gte' MongoDB operator.
	 * @param t Custom value to pair with current Key.
	 * @return A Key with Builded Documentation.
	 */
	template <class T>
	Key & operator >= ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$gte", t ) ) ) );
		return *this;
	}

	/**
	 * Use operator '>' to create a document with '$gt' MongoDB operator.
	 * @param t Custom value to pair with current Key.
	 * @return A Key with Builded Documentation.
	 */
	template <class T>
	Key & operator > ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, make_document( kvp( "$gt", t ) ) ) );
		return *this;
	}

	template <class T>
	Key & operator = ( T && t )
	{
		cDocumentation.doc = make_document( kvp( strKeyName, t ) );
		return *this;
	}

	/**
	 * Use operator '=' to create a document with '$set' MongoDB operator.
	 * @param sKey Key to get your Builder and make the Document.
	 * @return A Key with Builded Documentation.
	 */
	Key & operator = ( Key & sKey )
	{
		sKey.cBuilder.append( sKey.cDocumentation );
		cDocumentation.doc = make_document( kvp( "$set", sKey.cBuilder.view() ) );
		return *this;
	}

	/**
	 * Use operator '||' to create a document with '$or' MongoDB operator.
	 * @param sSubArray Generated Array to use when create the corresponding Document.
	 * @return A Key with Builded Documentation.
	 */
	Key & operator || ( SubArray & sSubArray )
	{
		cDocumentation.doc = make_document( kvp( "$or", sSubArray.View() ) );
		return *this;
	}

	/**
	 * Use operator '&&' to create a document with '$and' MongoDB operator.
	 * @param sSubArray Generated Array to use when create the corresponding Document.
	 * @return A Key with Builded Documentation.
	 */
	Key & operator && ( SubArray & sSubArray )
	{
		cDocumentation.doc = make_document( kvp( "$and", sSubArray.View() ) );
		return *this;
	}

	/**
	 * Use operator '+' to concatenate Documentations in the primary Key Builder.
	 * @param sKey Key to concatenate the Document.
	 * @return A Key with Builded Documentation.
	 */
	Key & operator + ( Key & sKey )
	{
		cBuilder.append( sKey.cDocumentation );
		return *this;
	}
private:
	std::string									strKeyName;
	bsoncxx::builder::concatenate_doc			cDocumentation;
	bsoncxx::builder::basic::document			cBuilder;
};
}
