SELECT name FROM people
WHERE id in
    (SELECT DISTINCT(people.id)
       FROM people, directors, ratings
      WHERE people.id = directors.person_id
        AND directors.movie_id = ratings.movie_id
        AND ratings.rating >= 9);