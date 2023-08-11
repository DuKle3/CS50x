CREATE TABLE transacted (
    user_id INTEGER,
    symbol TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price FLOAT NOT NULL,
    time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );