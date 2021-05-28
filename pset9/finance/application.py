import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id ORDER BY symbol ASC", user_id=session["user_id"])

    # get user from DB
    user = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])

    # init local variables
    total = 0
    total_stocks = 0
    cash = user[0]["cash"]

    # get stocks total sum
    def getTotalStocks(total_stocks):
        for stock in stocks:
            total_stocks = total_stocks + (stock["total"])
        return total_stocks + cash
    total = getTotalStocks(total_stocks)

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a posative integer", 400)

        action = "BUY"

        # stock data lookup
        stock = lookup(symbol)
        date = datetime.datetime.now().strftime("%Y-%m-%d %H.%M.%S")

        if not request.form.get("symbol"):
            return apology("add symbol")

        if not request.form.get("shares") or int(request.form.get("shares")) < 1:
            return apology("add numeric shares")

        # if does not exist
        if not stock:
            return apology("symbol not found")

        total = float(stock["price"]) * float(shares)

        # get user from DB
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
        cash = float(user[0]["cash"])

        # if user has low cash
        if cash < total:
            return apology("not enough cash")

        cash_left = cash - total

        stocks_in_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                                  user_id=user_id, symbol=symbol)

        if len(stocks_in_db) > 0:
            new_shares = int(stocks_in_db[0]["shares"]) + int(shares)
            new_total = float(stocks_in_db[0]["total"]) + total

            db.execute("UPDATE stocks SET shares = :shares, total = :total, price = :price WHERE user_id = :user_id AND symbol = :symbol",
                       user_id=user_id, symbol=symbol, shares=new_shares, price=stock["price"], total=new_total)
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, shares, price, total, name) VALUES (:user_id, :symbol, :shares, :price, :total, :name)",
                       user_id=user_id, symbol=symbol, shares=shares, price=stock["price"], total=total, name=stock["name"])

        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash_left, id=user_id)

        # add row to history
        db.execute("INSERT INTO history (user_id, action, symbol, shares, date) VALUES (:user_id, :action, :symbol, :shares, :date)",
                   user_id=user_id, action=action, symbol=symbol, shares=shares, date=date)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history = db.execute("SELECT * FROM history WHERE user_id = :user_id ORDER BY date DESC", user_id=user_id)
    return render_template("history.html", history=history)


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
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("empty symbol")

        # get stock data
        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("symbol not found")

        return render_template("quote_result.html", symbol=stock["symbol"], name=stock["name"], price=stock["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")

        if not request.form.get("password"):
            return apology("must provide password")

        if not request.form.get("confirmation"):
            return apology("must provide confirm")

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("must passwords be equal")

        username = request.form.get("username").lower()
        password = request.form.get("password")
        password_confirm = request.form.get("confirmation")
        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        if len(rows) >= 1:
            return apology("user already exists")

        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=hash)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        action = "SELL"

        stock = lookup(symbol)
        date = datetime.datetime.now().strftime("%Y-%m-%d %H.%M.%S")

        if not request.form.get("shares") or int(request.form.get("shares")) < 1:
            return render_template("sell.html")

        if not stock:
            return apology("symbol not found")

        total = float(stock["price"]) * float(shares)

        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
        cash = float(user[0]["cash"])

        cash_income = cash + total

        stocks_in_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                                  user_id=user_id, symbol=symbol)

        if int(shares) > int(stocks_in_db[0]["shares"]):
            return apology("you have not so many stocks")
        elif int(shares) == int(stocks_in_db[0]["shares"]):
            db.execute("DELETE FROM stocks WHERE user_id = :user_id AND symbol = :symbol", user_id=user_id, symbol=symbol)
        else:
            new_shares = int(stocks_in_db[0]["shares"]) - int(shares)
            new_total = float(stocks_in_db[0]["total"]) - total

            db.execute("UPDATE stocks SET shares = :shares, total = :total, price = :price WHERE user_id = :user_id AND symbol = :symbol",
                       user_id=user_id, symbol=symbol, shares=new_shares, price=stock["price"], total=new_total)

        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash_income, id=user_id)

        # add row to history
        db.execute("INSERT INTO history (user_id, action, symbol, shares, date) VALUES (:user_id, :action, :symbol, :shares, :date)",
                   user_id=user_id, action=action, symbol=symbol, shares=shares, date=date)

        return redirect("/")
    else:
        stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id", user_id=session["user_id"])

        return render_template("sell.html", stocks=stocks)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    if request.method == "POST":
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
        cash = float(user[0]["cash"])
        cash_income = float(cash) + float(request.form.get("cash"))

        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash_income, id=user_id)

        return redirect("/")
    else:
        return render_template("add.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
