SELECT movies.title
  FROM movies, ratings, stars, people
 WHERE movies.id = ratings.movie_id
   AND movies.id = stars.movie_id
   AND stars.person_id = people.id
   AND people.name = 'Chadwick Boseman'
 ORDER BY ratings.rating DESC
 LIMIT 5;