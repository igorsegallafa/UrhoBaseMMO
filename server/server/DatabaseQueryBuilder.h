#pragma once

#include "DatabaseKey.h"
#include "DatabaseSubArray.h"

namespace Database
{
class QueryBuilder
{
public:
	//Constructor
												QueryBuilder() = default;

	/**
	 * Append a Document to current Query Builder.
	 * @param sKey Key to get your Document and append it on Builder.
	 */
	void										AppendParam( Key & sKey ){ cBuilder.append( sKey.Documentation() ); };

	/**
	 * Clear Document Builder.
	 */
	void										Clear(){ cBuilder.clear(); }

	/**
	 * @return A current Document Builder.
	 */
	inline bsoncxx::builder::basic::document  & Builder()
	{
		return cBuilder;
	}

	/**
	 * @return A view of the current Document Builder.
	 */
	inline bsoncxx::document::view_or_value		View() const
	{
		return cBuilder.view();
	}
private:
	bsoncxx::builder::basic::document			cBuilder{};
};
}