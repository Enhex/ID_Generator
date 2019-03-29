#include <ID_Generator.h>

int main()
{
	ID_Generator<unsigned> id_gen;
	auto id = id_gen.create();
}
