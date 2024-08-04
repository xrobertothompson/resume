from flask import Flask, request, render_template, redirect, url_for, flash, session, jsonify
import json
import os
from flask_bcrypt import Bcrypt
from functools import wraps
import sqlite3
from werkzeug.utils import secure_filename

app = Flask(__name__, template_folder='templates')
app.secret_key = os.urandom(24)  # Use a random secret key for security
bcrypt = Bcrypt(app)

UPLOAD_FOLDER = 'static/uploads'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg', 'gif'}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    conn = sqlite3.connect('triptimate.db')
    conn.row_factory = sqlite3.Row
    return conn

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'user_id' not in session:
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    return decorated_function

@app.context_processor
def inject_user():
    if 'user_id' in session:
        with get_db_connection() as conn:
            user = conn.execute('SELECT * FROM users WHERE user_id = ?', (session['user_id'],)).fetchone()
        return dict(current_user=user)
    return dict(current_user=None)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        email = request.form['email']
        return redirect(url_for('register', email=email))
    return render_template('index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        confirmation = request.form['confirmation']

        if not email or not password or not confirmation:
            flash('Please fill out all fields', 'error')
            return redirect(url_for('register'))

        if password != confirmation:
            flash('Passwords do not match', 'error')
            return redirect(url_for('register'))

        hashed_password = bcrypt.generate_password_hash(password).decode('utf-8')

        try:
            with get_db_connection() as conn:
                conn.execute("INSERT INTO users (email, password) VALUES (?, ?)", (email, hashed_password))
                conn.commit()
            flash('Registration successful! Please log in.', 'success')
            return redirect(url_for('login'))
        except sqlite3.IntegrityError:
            flash('Email already registered', 'error')

    email = request.args.get('email')
    return render_template('register.html', email=email)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        with get_db_connection() as conn:
            user = conn.execute("SELECT * FROM users WHERE email = ?", (email,)).fetchone()

        if user and bcrypt.check_password_hash(user['password'], password):
            session['user_id'] = user['user_id']
            session['email'] = user['email']
            flash('Login successful!', 'success')
            return redirect(url_for('index'))
        else:
            flash('Invalid email or password', 'error')

    return render_template('login.html')

@app.route('/logout')
def logout():
    session.clear()
    flash('You have been logged out.', 'success')
    return redirect(url_for('index'))

@app.route('/about', methods=['GET'])
def about():
    return render_template('about.html')

@app.route('/tips')
@login_required
def tips():
    # Fetch travel plans to be included in the planner section
    conn = get_db_connection()
    plans = conn.execute('SELECT * FROM travel_plans').fetchall()
    conn.close()

    # Render planner.html with the plans data
    planner_content = render_template('planner.html', plans=plans)

    # Render tips.html and pass the planner content to it
    return render_template('tips.html', planner_content=planner_content)

@app.route('/profile', methods=['GET', 'POST'])
def profile():
    if 'user_id' not in session:
        flash('Please log in to view your profile.', 'error')
        return redirect(url_for('login'))
    
    with get_db_connection() as conn:
        user = conn.execute('SELECT * FROM users WHERE user_id = ?', (session['user_id'],)).fetchone()

    if request.method == 'POST':
        if 'profile_pic' not in request.files:
            flash('No file part', 'error')
            return redirect(request.url)
        
        file = request.files['profile_pic']
        if file.filename == '':
            flash('No selected file', 'error')
            return redirect(request.url)
        
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            try:
                file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))

                with get_db_connection() as conn:
                    conn.execute('UPDATE users SET profile_pic = ? WHERE user_id = ?', (filename, session['user_id']))
                    conn.commit()

                flash('Profile picture updated!', 'success')
                return redirect(url_for('profile'))
            except Exception as e:
                flash(f'Error saving file: {e}', 'error')
    
    return render_template('profile.html', current_user=user)

@app.route('/map')
def map():
    return render_template('map.html')

@app.route('/planner')
def planner():
    conn = get_db_connection()
    plans = conn.execute('SELECT * FROM travel_plans').fetchall()
    print(plans)  # Debugging
    conn.close()
    return render_template('planner.html', plans=plans)

@app.route('/create', methods=['GET', 'POST'])
def create():
    if request.method == 'POST':
        origin = request.form['from']
        destination = request.form['destination']
        budget = request.form['budget']
        num_travelers = request.form['travelers']
        departure_date = request.form['departure']
        return_date = request.form['return']

        conn = get_db_connection()
        conn.execute('INSERT INTO travel_plans (origin, destination, budget, num_travelers, departure_date, return_date) VALUES (?,?,?,?,?,?)',
                     (origin, destination, budget, num_travelers, departure_date, return_date))
        conn.commit()
        conn.close()

        # Redirect to tips page which will include updated planner content
        return redirect(url_for('tips'))

    return render_template('create.html')

@app.route('/tipscont')
def tipscont():
    return render_template('tipscont.html')


if __name__ == '__main__':
    app.run(debug=True)
