#include <list>
#include <string>
#include "inventory.h"

// Sets total number of copies in the system
void Inventory::set_total_copies(const int total_copies)
{
    total_copies_ = total_copies;
    copies_ = total_copies;
}

// Adds copies if DVD is already in the system
void Inventory::add_copies(const int copies)
{
    total_copies_ += copies;
    copies_ += copies;
}