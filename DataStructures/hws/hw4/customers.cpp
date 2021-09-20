#include <list>
#include <string>
#include "customers.h"

// Loops through each item in movies received list
bool Customers::has_movie(const std::string &dvd_name)
{
    for (string_type::iterator movies_received_itr = movies_received_.begin(); movies_received_itr != movies_received_.end(); movies_received_itr++)
    {
        if (*movies_received_itr == dvd_name)
        {
            return true;
        }
    }
    return false; // If customer doesn't have movie, return false
}

void Customers::receives(const std::string &dvd_name)
{
    movies_received_.push_back(dvd_name);
    for (string_type::iterator preferences_itr = preferences_.begin(); preferences_itr != preferences_.end(); preferences_itr++)
    {
        if (*preferences_itr == dvd_name)
        {
            preferences_itr = preferences_.erase(preferences_itr);
            break;
        }
    }
}