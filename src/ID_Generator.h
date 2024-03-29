#pragma once


#include <cassert>
#include <limits>
#include <unordered_set>

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

	// return true if added, false if already taken.
	bool add(ID id);

	// Removes an ID and reuse it later
	void remove(const ID id);

	void reset();

protected:
	ID highest_ID = invalid_id; // highest used ID
	std::unordered_set<ID> unused_IDs;
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
		// consume an unused ID
		auto iter = unused_IDs.begin();
		id = *iter;
		unused_IDs.erase(iter);

		if (id > highest_ID)
			highest_ID = id;
	}
	else
	{
		id = ++highest_ID; // if it's the first ID and highest_ID is invalid, it will range-loop to 0
	}

	return id;
}


template<typename ID>
bool ID_Generator<ID>::add(ID id)
{
	if(highest_ID != invalid_id && id <= highest_ID)
	{
		if(id == highest_ID)
			return false;

		// check if ID is unused
		if(unused_IDs.count(id) == 0)
			return false;
		// if it's above highest ID it can't be an unused ID
		unused_IDs.erase(id);
	}
	else
	{
		if (highest_ID == invalid_id) {
			highest_ID = 0;
		}
		else {
			// starting highest_ID is used, so skip adding it to the unused IDs
			++highest_ID;
		}

		// add all the IDs between highest_ID and the new ID to the unused IDs
		for (; highest_ID < id; ++highest_ID) {
			unused_IDs.emplace(highest_ID);
		}
	}

	return true;
}


template<typename ID>
void ID_Generator<ID>::remove(const ID id)
{
	if(id == highest_ID) {
		--highest_ID;
		// find the highest used ID
		// remove unused IDs above the new highest used ID
		while(unused_IDs.count(highest_ID) != 0){
			unused_IDs.erase(highest_ID);
			--highest_ID; //NOTE: if reaching invalid ID unused_IDs should be empty, thus equivilant to reset()
		}
	}
	else {
		unused_IDs.emplace(id);
	}
}

template<typename ID>
void ID_Generator<ID>::reset()
{
	unused_IDs.clear();
	highest_ID = invalid_id;
}