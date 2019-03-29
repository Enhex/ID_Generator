#pragma once


#include <cassert>
#include <limits>
#include <vector>

/*
Generates unique IDs
- NOTE: ID should be an unsigned integer type.
*/
template<typename ID>
struct ID_Generator
{
	static constexpr ID invalid_id = std::numeric_limits<ID>::max();

	// Create a new ID
	ID create();

	// Removes an ID and reuse it later
	void remove(const ID id);

	void reset();

protected:
	ID highest_ID = invalid_id;
	std::vector<ID> unused_IDs;
};




//
// Definitions
//

template<typename ID>
ID ID_Generator<ID>::create()
{
	ID id;

	if (unused_IDs.size() > 0)
	{
		id = unused_IDs.back();
		unused_IDs.pop_back();

		if (id > highest_ID)
			highest_ID = id;
	}
	else
	{
		id = ++highest_ID;
	}

	return id;
}


template<typename ID>
void ID_Generator<ID>::remove(const ID id)
{
	unused_IDs.push_back(id);
}

template<typename ID>
void ID_Generator<ID>::reset()
{
	unused_IDs.clear();
	highest_ID = invalid_id;
}