#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "utility.h"
using namespace std;

MovieDatabase::MovieDatabase()
{
    isload = false;// Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    if(isload)
        return false;
    std::ifstream inFile(filename);
    if(!inFile)
        return false;
    std::string name, year, id, line;
    float num;
    while(getline(inFile, id)&&getline(inFile, name) && getline(inFile, year))
    {
        std::vector<std::string> dir;
        std::vector<std::string> act;
        std::vector<std::string> gen;
        getline(inFile, line);
        std::stringstream ss(line);
        std::string direc, actor, genre;
        while(getline(ss, direc, ','))
        {
            dir.push_back(lowerCase(direc));
        }
        getline(inFile, line);
        std::stringstream ss1(line);
        while(getline(ss1, actor, ','))
            act.push_back(lowerCase(actor));
        getline(inFile, line);
        std::stringstream ss2(line);
        while(getline(ss2, genre, ','))
            gen.push_back(lowerCase(genre));
        getline(inFile, line);
        num = stof(line);
        Movie nMovie(lowerCase(id), name, year, dir, act, gen, num);
        m_movie.insert(lowerCase(id), nMovie);
        addList(dir, nMovie, dir_movie);
        addList(act, nMovie, act_movie);
        addList(gen, nMovie, gen_movie);
        if(getline(inFile, line)&&line.empty())
            continue;
    }
    return true;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie>::Iterator it;
    it = m_movie.find(lowerCase(id));
    Movie* p = &it.get_value();
    return p;// Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return get_movies_with_item(director, dir_movie);// Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return get_movies_with_item(actor, act_movie);
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return get_movies_with_item(genre, gen_movie); 
}

std::vector<Movie*> MovieDatabase::get_movies_with_item(const std::string& item, const TreeMultimap<std::string, Movie> &tree) const
{
    std::vector<Movie*> movies;
    TreeMultimap<std::string, Movie>::Iterator it;
    it = tree.find(lowerCase(item));
    while(it.is_valid())
    {
        Movie* p=&it.get_value();
        movies.push_back(p);
      //  std::cerr<<movies[movies.size()-1]->get_id()<<std::endl;
        it.advance();
    }
    
    return movies;
}

void MovieDatabase::addList(const std::vector<std::string>& item, const Movie &m, TreeMultimap<std::string, Movie> &tree)
{
    for(int i = 0; i<item.size(); i++)
    {
        std::string item_name = item[i];
        tree.insert(item_name, m);
    }
}
