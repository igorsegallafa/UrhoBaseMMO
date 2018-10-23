#pragma once

#include "DatabaseQueryBuilder.h"

namespace Database
{
template <typename T>
class Model
{
	friend T;
public:
								Model() = default;

	/**
	 * Return a collection that class is holding.
	 */
	static mongocxx::collection	Collection(){ return cCollection; }

	/**
	 * Set a Collection on database entry model.
	 * @param cNewCollection Collection to class hold statically
	 */
	static void					SetCollection( const mongocxx::collection & cNewCollection ){ cCollection = cNewCollection; }
private:
	static						mongocxx::collection cCollection;
};
template <typename T> mongocxx::collection Model<T>::cCollection{};
}