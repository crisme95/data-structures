// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "inventory.h"
#include "customers.h"

// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<Inventory> inventory_type;
typedef std::list<Customers> customers_type;
typedef std::list<std::string> preference_type;

// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// Search function prototypes
bool check_inventory(inventory_type &inventory, const std::string &dvd_name);
bool check_customers(customers_type &customers, const std::string &customer_name);
bool check_preferences(preference_type &preferences, const std::string &dvd_name);

// ==================================================================

void usage(const char *program_name)
{
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}

int main(int argc, char *argv[])
{

  if (argc < 3 || argc > 5)
  {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr)
  {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]);
  }
  std::ofstream ostr(argv[2]);
  if (!ostr)
  {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]);
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++)
  {
    if (std::string(argv[i]) == "--improved")
    {
      use_improved_algorithm = true;
    }
    else if (std::string(argv[i]) == "--analysis")
    {
      print_analysis = true;
    }
    else
    {
      usage(argv[0]);
    }
  }

  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;

  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token)
  {
    if (token == "dvd")
    {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;

      // Checks if DVD already exists in inventory
      if (check_inventory(inventory, dvd_name) == true)
      {
        for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++)
        {
          if (inventory_itr->get_name() == dvd_name)
          {
            inventory_itr->add_copies(copies); // Adds copies to inventory
            if (copies > 1)
            {
              ostr << copies << " copies of " << inventory_itr->get_name() << " added" << std::endl;
            }
            else
            {
              ostr << copies << " copy of " << inventory_itr->get_name() << " added" << std::endl;
            }
            break;
          }
        }
      }
      // If DVD doesn't already exist, create new Inventory object
      else
      {
        Inventory temp_dvd;
        temp_dvd.set_name(dvd_name);
        temp_dvd.set_total_copies(copies);
        inventory.push_back(temp_dvd);

        if (copies > 1)
        {
          ostr << temp_dvd.get_copies() << " copies of " << temp_dvd.get_name() << " added" << std::endl;
        }
        else
        {
          ostr << temp_dvd.get_copies() << " copy of " << temp_dvd.get_name() << " added" << std::endl;
        }
      }
    }
    else if (token == "customer")
    {
      std::string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;
      bool name_check = false; // Stays false if customer exists in the system

      // Checks if customer already exists in the system
      if (check_customers(customers, customer_name) == true)
      {
        ostr << "WARNING: Already have a customer named " << customer_name << std::endl;
      }
      else
      {
        name_check = true;
      }

      Customers temp_customer;
      temp_customer.set_name(customer_name);
      preference_type temp_pref;

      for (int i = 0; i < num_movies; i++)
      {
        std::string dvd_name = read_dvd_name(istr);

        // checks if DVD exists
        if (check_inventory(inventory, dvd_name) == false)
        {
          ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
        }
        else
        {
          temp_customer.add_preferences(dvd_name);
        }
      }

      // Customer object only gets added if name isn't a duplicate
      if (name_check == true)
      {
        customers.push_back(temp_customer);
        ostr << "new customer: " << customer_name << std::endl;
      }
    }
    else if (token == "ship")
    {
      shipping_algorithm(inventory, customers, ostr);
    }
    else if (token == "return_oldest")
    {
      std::string customer_name = read_customer_name(istr);

      // checks if customer exists
      if (check_customers(customers, customer_name) == true)
      {
        for (customers_type::iterator customers_itr = customers.begin(); customers_itr != customers.end(); customers_itr++)
        {
          if (customers_itr->get_name() == customer_name)
          {
            ostr << customer_name << " returns " << customers_itr->get_movies_received().front() << std::endl;

            // Loop that finds the DVD title and adds back the copy
            for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++)
            {
              if (inventory_itr->get_name() == customers_itr->get_movies_received().front())
              {
                inventory_itr->returned();
                break;
              }
            }
            customers_itr->return_oldest();
            break;
          }
        }
      }
    }
    else if (token == "return_newest")
    {
      std::string customer_name = read_customer_name(istr);
      // checks if customer exists
      if (check_customers(customers, customer_name) == true)
      {
        for (customers_type::iterator customers_itr = customers.begin(); customers_itr != customers.end(); customers_itr++)
        {
          if (customers_itr->get_name() == customer_name)
          {
            ostr << customer_name << " returns " << customers_itr->get_movies_received().back() << std::endl;

            // Loop that finds the DVD title and adds back the copy
            for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++)
            {
              if (inventory_itr->get_name() == customers_itr->get_movies_received().back())
              {
                inventory_itr->returned();
                break;
              }
            }
            customers_itr->return_newest();
            break;
          }
        }
      }
    }
    else if (token == "print_customer")
    {
      std::string customer_name = read_customer_name(istr);

      // checks if customer exists
      if (check_customers(customers, customer_name) == true)
      {
        for (customers_type::iterator customers_itr = customers.begin(); customers_itr != customers.end(); customers_itr++)
        {
          if (customers_itr->get_name() == customer_name)
          {
            // checks if customer has 1 or more movies
            if (customers_itr->get_num_movies() > 0)
            {
              ostr << customers_itr->get_name() << " has " << customers_itr->get_num_movies() << " movies:" << std::endl;
            }

            // if not, prints out that the customer has no movies
            else
            {
              ostr << customers_itr->get_name() << " has no movies" << std::endl;
            }

            preference_type movies_received = customers_itr->get_movies_received();
            for (preference_type::iterator movies_received_itr = movies_received.begin(); movies_received_itr != movies_received.end(); movies_received_itr++)
            {
              ostr << "    " << *movies_received_itr << std::endl;
            }

            // checks if preference list is empty
            if (customers_itr->preference_list_empty() == false)
            {
              ostr << "  preference list:" << std::endl;
              preference_type preferences = customers_itr->get_preferences();
              for (preference_type::iterator preferences_itr = preferences.begin(); preferences_itr != preferences.end(); preferences_itr++)
              {
                ostr << "    " << *preferences_itr << std::endl;
              }
            }
            break;
          }
        }
      }
      else
      {
        ostr << "WARNING: No customer named " << customer_name << std::endl;
      }
    }
    else if (token == "print_dvd")
    {
      std::string dvd_name = read_dvd_name(istr);

      // checks if DVD exists in the inventory
      if (check_inventory(inventory, dvd_name) == true)
      {
        for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++)
        {
          if (inventory_itr->get_name() == dvd_name)
          {
            ostr << inventory_itr->get_name() << ":" << std::endl;
            // checks if there's still copies available
            if (inventory_itr->get_total_copies() - inventory_itr->get_copies() > 0)
            {
              // checks if copies checked out and copies available are greater than 1
              if (inventory_itr->get_total_copies() - inventory_itr->get_copies() > 1 && inventory_itr->get_copies() > 1)
              {
                ostr << "  " << (inventory_itr->get_total_copies() - inventory_itr->get_copies()) << " copies checked out and " << inventory_itr->get_copies() << " copies available" << std::endl;
              }
              // checks if copies checked out is 1 and copies available is more than 1
              else if (inventory_itr->get_total_copies() - inventory_itr->get_copies() == 1 && inventory_itr->get_copies() > 1)
              {
                ostr << "  " << (inventory_itr->get_total_copies() - inventory_itr->get_copies()) << " copy checked out and " << inventory_itr->get_copies() << " copies available" << std::endl;
              }
              // checks if copies checked out is more than 1 and copies available is 1
              else if (inventory_itr->get_total_copies() - inventory_itr->get_copies() > 1 && inventory_itr->get_copies() == 1)
              {
                ostr << "  " << (inventory_itr->get_total_copies() - inventory_itr->get_copies()) << " copies checked out and " << inventory_itr->get_copies() << " copy available" << std::endl;
              }
              // checks if copies checked out and copies available is 1
              else if (inventory_itr->get_total_copies() - inventory_itr->get_copies() == 1 && inventory_itr->get_copies() == 1)
              {
                ostr << "  " << (inventory_itr->get_total_copies() - inventory_itr->get_copies()) << " copy checked out and " << inventory_itr->get_copies() << " copy available" << std::endl;
              }
              // all copies checked out and none available
              else
              {
                if (inventory_itr->get_total_copies() - inventory_itr->get_copies() > 1)
                {
                  ostr << "  " << (inventory_itr->get_total_copies() - inventory_itr->get_copies()) << " copies checked out" << std::endl;
                }
                else
                {
                  ostr << "  " << (inventory_itr->get_total_copies() - inventory_itr->get_copies()) << " copy checked out" << std::endl;
                }
              }
            }
            else
            {
              if (inventory_itr->get_total_copies() > 1)
              {
                ostr << "  " << inventory_itr->get_total_copies() << " copies available" << std::endl;
              }
              else
              {
                ostr << "  " << inventory_itr->get_total_copies() << " copy available" << std::endl;
              }
            }
            break;
          }
        }
      }
      else
      {
        ostr << "WARNING: No movie named " << dvd_name << std::endl;
      }
    }
    else if (token == "add_preference")
    {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);

      // checks if customer exists
      if (check_customers(customers, customer_name) == false)
      {
        ostr << "WARNING: no customer named " << customer_name << std::endl;
      }
      // checks if DVD exists
      else if (check_inventory(inventory, dvd_name) == false)
      {
        ostr << "WARNING: no movie named " << dvd_name << "in the inventory" << std::endl;
      }
      else
      {
        for (customers_type::iterator customers_itr = customers.begin(); customers_itr != customers.end(); customers_itr++)
        {
          if (customers_itr->get_name() == customer_name)
          {
            preference_type preferences = customers_itr->get_preferences();
            if (check_preferences(preferences, dvd_name) == false)
            {
              customers_itr->add_preferences(dvd_name);
            }
            else
            {
              ostr << "WARNING: " << dvd_name << " already exists in preference list" << std::endl;
            }
            break;
          }
        }
      }
    }
    else
    {
      std::cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }
  }
}

// ==================================================================

// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr)
{
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}

// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr)
{
  std::string token;
  istr >> token;
  assert(token[0] == '"');
  std::string answer = token;
  while (answer[answer.size() - 1] != '"')
  {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}

// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name)
{
  for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++)
  {
    if (inventory_itr->get_name() == dvd_name)
    {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}

// A search function to check if DVD already exists in the inventory
bool check_inventory(inventory_type &inventory, const std::string &dvd_name)
{
  for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++)
  {
    if (inventory_itr->get_name() == dvd_name)
    {
      return true;
      break;
    }
  }
  // if the DVD doesn't already exist in inventory, return false
  return false;
}

// A search function to check if customer already exists in the system
bool check_customers(customers_type &customers, const std::string &customer_name)
{
  for (customers_type::iterator customers_itr = customers.begin(); customers_itr != customers.end(); customers_itr++)
  {
    if (customers_itr->get_name() == customer_name)
    {
      return true;
      break;
    }
  }
  // if the customer doesn't already exist in inventory, return false
  return false;
}

bool check_preferences(preference_type &preferences, const std::string &dvd_name)
{
  for (preference_type::iterator preferences_itr = preferences.begin(); preferences_itr != preferences.end(); preferences_itr++)
  {
    if (*preferences_itr == dvd_name)
    {
      return true;
      break;
    }
  }

  // if DVD wasn't a duplicate, return false
  return false;
}

// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr)
{

  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end())
  {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() == true || customer_itr->preference_list_empty() == true)
    {
      // move on to the next customer
      customer_itr++;
      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;

    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
    for (preference_type::const_iterator preferences_itr = preferences.begin();
         preferences_itr != preferences.end(); preferences_itr++)
    {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory, *preferences_itr);
      if (inventory_itr != inventory.end() && inventory_itr->available() == true && customer_itr->has_movie(*preferences_itr) == false)
      {

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
        inventory_itr->shipped();
        customer_itr->receives(*preferences_itr);

        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd)
    {
      customer_itr++;
    }
  }
}

// ==================================================================
