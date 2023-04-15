#ifndef MovieDatabase_h
#define MovieDatabase_h

#include <string>
#include <vector>
#include "treemm.h"
#include <cctype>
#include "Movie.h"
#include "utility.h"
class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

    
  private:

    
    void addList(const std::vector<std::string>& item, const Movie &m, TreeMultimap<std::string, Movie> &tree);
    std::vector<Movie*> get_movies_with_item(const std::string& item, const TreeMultimap<std::string, Movie> &tree) const;
    TreeMultimap<std::string, Movie> m_movie;
    TreeMultimap<std::string, Movie> dir_movie;
    TreeMultimap<std::string, Movie> act_movie;
    TreeMultimap<std::string, Movie> gen_movie;
    bool isload;
};

#endif // MOVIEDATABASE_INCLUDED

