#include "Puzzle.hpp"
#include "PruningTable.hpp"

#include <cstdlib>
#include <cstdio>

// std::size_t max = 2500*1024*1024;
// char *ptr = nullptr;

// std::size_t allocated = 0;

// void* operator new(std::size_t sz) {
// 	auto tmp = ptr;
// 	ptr += sz;
// 	allocated += sz;
// 	return (void*)tmp;
// }

// void operator delete(void *ptr) noexcept {
// 	; // no-op
// }

int main()
{
	// ptr = (char*)malloc(max);
	Puzzle p = get_cross();
	auto base_moves = init_three_moves();
	PruningTable pt = gen_pruning_table(p, 8, base_moves);
	// printf("%lu\n", pt.size());
	// printf("%lu\n", allocated);
	return 0;
}