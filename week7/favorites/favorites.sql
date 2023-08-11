CREATE TABLE houses (
    id INTEGER NOT NULL,
    house TEXT NOT NULL,
    head TEXT NOT NULL
);

CREATE TABLE assignments (
    student_id INTEGER NOT NULL,
    house_id INTEGER NOT NULL,
    FOREIGN KEY (student_id) REFERENCEs students(id),
    FOREIGN KEY (house_id) REFERENCES houses(id)
);

ALTER TABLE Persons
ADD PRIMARY KEY (ID);