# Movie_Recommending_System
This is a project for class CS32.
This project aims to practice students' techniques in implementing and using template class, binary tree, iterator, map, set, and hash_map.
This movie-recommending system will provide recommendations for up to 20K movies for up to 100K users.
-Each user has a history of movies they've watched (up to hundreds of movies)
-Each movie has a set of attributes that describe it, including the movie title, release year,
director(s), actor(s), genre(s) like horror, romance, etc., and a movie rating (e.g., 3.5 stars)

TO identify recommended movies for a given person P, the system determines what attributes are associated with the movies P has watched in the past, and then identifies new movies that also share as many of those attributes as possible.

The project consists of a total of six classes that were completed by the student:

● User: A class that represents a user and their movie-watching history

● UserDatabase: A class that stores all of the user objects and is searchable (e.g., find
the user object associated with a given email address)

● Movie: A class that represents a movie, including a unique movie ID (e.g., ID15344), its
title, release year, director(s), actor(s), genre(s), and star rating

● MovieDatabase: A class that stores all of the movie objects and is searchable (e.g.,
given a movie ID give me its movie object, or given an actor's name, give me all the
movies starring that actor, etc.)

● Recommender: A class that produces rank-ordered movie recommendations for a given
user given their previous watching history. Data in this class is managed using a hash table.

● TreeMultimap: A templated class that implements a multimap that maps each key to
one or more values, using a binary search tree1 data structure

