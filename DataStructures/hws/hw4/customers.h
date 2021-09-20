#ifndef _customers_h_
#define _customers_h_

#include <list>
#include <string>

class Customers
{
public:
    typedef std::list<std::string> string_type;

    // Accessors
    std::string get_name() const { return name_; }
    std::list<std::string> get_preferences() const { return preferences_; }
    std::list<std::string> get_movies_received() const { return movies_received_; }
    int get_num_movies() const { return movies_received_.size(); }
    bool has_max_num_movies() const { return movies_received_.size() >= 3; } // Returns true if customer has 3 movies
    bool preference_list_empty() const { return preferences_.size() == 0; }  // Returns true if preference list is empty
    bool has_movie(const std::string &dvd_name);

    // Modifiers
    void set_name(const std::string &name) { name_ = name; }
    void add_preferences(const std::string &dvd_name) { preferences_.push_back(dvd_name); }
    void return_oldest() { movies_received_.pop_front(); }
    void return_newest() { movies_received_.pop_back(); }
    void receives(const std::string &dvd_name);

private:
    std::string name_;
    std::list<std::string> preferences_;     // List of preferences
    std::list<std::string> movies_received_; // List of movies received
};

#endif