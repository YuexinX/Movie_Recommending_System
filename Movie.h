#ifndef Movie_h
#define Movie_h

#include <string>
#include <vector>
#include <iostream>

class Movie
{
  public:
    Movie(const std::string& id, const std::string& title,
          const std::string& release_year,
          const std::vector<std::string>& directors,
          const std::vector<std::string>& actors,
          const std::vector<std::string>& genres, float rating);
    std::string get_id() const;
    std::string get_title() const;
    std::string get_release_year() const;
    float get_rating() const;
    std::vector<std::string> get_directors() const;
    std::vector<std::string> get_actors() const;
    std::vector<std::string> get_genres() const;

    
  private:
    std::string m_id, m_title, m_year;
    std::vector<std::string> m_dir;
    std::vector<std::string> m_act;
    std::vector<std::string> m_gen;
    float m_rate;
    
};

#endif // MOVIE_INCLUDED

