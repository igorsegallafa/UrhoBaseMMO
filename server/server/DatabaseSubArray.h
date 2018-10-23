#pragma once

namespace Database
{
class SubArray
{	
public:
	/**
	 * All cases to append value on Bson-cxx Array.
	 * @case 1 Any value different from class Key
	 * @case 2 Returned class Key from use with Operators (e.g. Key( keyName ) < 30 ); )
	 * @case 3 Returned class Key from use of Constructor (e.g. Key( keyName, keyValue ); )
	 */
	template <class T>
	void										AppendValue( T && t ){ cArray.append( t ); }
	void										AppendValue( class Key & sKey );
	void										AppendValue( class Key && sKey );

	/**
	 * Base-case to expansion of Variadic Template, on this case, do nothing.
	 */
	void										MakeArray(){};

	/**
	 * Appends Arguments of Variadic Template on Bson-cxx Array.
	 */
	template <typename Arg, typename... Args>
	void										MakeArray( Arg&& a, Args&&... args )
	{
		AppendValue( std::forward<Arg>( a ) );
		MakeArray( std::forward<Args>( args )... );
	}

	//Constructor
	template <typename... Args>
												SubArray( Args&&... args ){ MakeArray( std::forward<Args>( args )... ); }
	/**
	 * @return A view or Value of Array Builder.
	 */
	inline bsoncxx::array::view_or_value		View() const{ return cArray.view(); }

private:
	bsoncxx::builder::basic::array				cArray;
};
}