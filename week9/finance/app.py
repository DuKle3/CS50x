import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(shares) AS n FROM transacted WHERE user_id = ? GROUP BY symbol", session["user_id"])

    # calculate cash, total
    value = 0
    for row in rows:
        symbol = row["symbol"]

        # lookup the current price
        stock = lookup(symbol)
        price = stock["price"]
        row["price"] = price
        row["total"] = usd(price * row["n"])

        # sum the value of each stock
        value += price * row["n"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    return render_template("index.html", rows=rows, cash=usd(cash[0]["cash"]), total=usd(cash[0]["cash"]+value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # GET
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # look up the stock
        stock = lookup(symbol)

        # Invalid Symbol
        if not stock:
            return apology("invalid symbol", 400)

        # Invalid shares
        try:
            shares = int(shares)
        except:
            return apology("invalid shares", 400)
        if shares < 0:
            return apology("invalid shares", 400)

        id = session["user_id"]

        # if user can't afford it
        value = stock["price"] * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", id)
        if (cash[0]["cash"] - value) < 0:
            return apology("You can't afford it", 400)

        # UPDATE the cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"] - value, id)

        # INSERT record into table
        db.execute("INSERT INTO transacted (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)", id, symbol, shares, stock["price"])
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transacted WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # POST
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # look up the stock
        stock = lookup(symbol)

        # Invalid Symbol
        if not stock:
            return apology("invalid symbol", 400)

        stock["price"] = usd(stock["price"])
        return render_template("quote.html", method="post", stock=stock)

    # GET
    else:
        return render_template("quote.html", method="get")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure the username submitted
        username = request.form.get("username")
        password = request.form.get("password")
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)

        # Ensure the passwords match
        elif password != request.form.get("confirmation"):
            return apology("password don't match")

        # Ensure the username repeated
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 0:
            return apology("username already exists")

        # INSERT into users
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))

        # Login
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        # Redirect to home page
        return redirect("/")

    # GET --> register page
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session["user_id"]
    rows = db.execute("SELECT symbol, SUM(shares) AS n FROM transacted WHERE user_id = ? GROUP BY symbol;", id)
    if request.method == "POST":
        # Invalid symbol
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Invalid shares
        if not shares:
            return apology("Invalid shares", 400)

        for row in rows:
            if row["symbol"] == symbol:
                # Not enough shares
                if int(shares) > row["n"]:
                    return apology("Not enough shares", 400)
                else:
                    # Sell
                    stock = lookup(symbol)
                    value = stock["price"] * int(shares)
                    # UPDATE the cash
                    cash = db.execute("SELECT cash FROM users WHERE id = ?;", id)
                    db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash[0]["cash"] + value, id)

                    # INSERT record into table
                    shares = -int(shares)
                    db.execute("INSERT INTO transacted (user_id, symbol, shares, price) VALUES(?, ?, ?, ?);", id, symbol, shares, stock["price"])
                    return redirect("/")
        # No symbol
        return apology("Please choose a Symbol", 400)
    else:
        return render_template("sell.html", rows=rows)


@app.route("/addCash", methods=["GET", "POST"])
@login_required
def addCash():
    if request.method == "POST":
        id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", id)
        value = request.form.get("addCash")

        # add the value to cash
        sum = cash[0]["cash"] + int(value)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", sum, id)
        return redirect("/")
    else:
        return render_template("addCash.html")


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "POST":
        # confirm password
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure username exists and password is correct
        if not check_password_hash(rows[0]["hash"], request.form.get("currentPassword")):
            return apology("invalid password", 403)

        newPassword = request.form.get("newPassword")
        if not newPassword:
            return apology("invalid password", 403)
        # Update the password
        db.execute("UPDATE users SET hash = ? WHERE id = ?;", generate_password_hash(newPassword), session["user_id"])
        return redirect("/")
    else:
        return render_template("change.html")