from flask import Flask, jsonify, request
import json

# Initialize the Flask application
app = Flask(__name__)

# Define a route to create an endpoint
@app.route('/', methods=['GET'])
def home():
    return jsonify({"message": "Welcome to the Flask API!"})

# Example of a GET request with parameters
@app.route('/api/data', methods=['GET'])
def get_data():
    data = {
        "name": "John Doe",
        "age": 30,
        "job": "Developer"
    }
    return jsonify(data)

# Example of a POST request
@app.route('/api/data', methods=['POST'])
def post_data():
    data = request.get_json()

    # Open (or create) a file to save the data
    with open('data.json', 'w') as f:
        json.dump(data, f, indent=4)

    response = {
        "message": "Data received successfully",
        "received_data": data
    }
    return jsonify(response), 201

@app.route('/api/saved-data', methods=['GET'])
def get_saved_data():
    try:
        # Open and read the saved data from the file
        with open('data.json', 'r') as f:
            saved_data = json.load(f)
        return jsonify(saved_data), 200  # Return the saved data as JSON
    except FileNotFoundError:
        return jsonify({"error": "No data found. Please save data first."}), 404

# Run the Flask app
if __name__ == '__main__':
    #app.run(debug=True)
    #app.run(host='192.168.43.105', port=5000, debug=True)
    app.run(host='192.168.0.15', port=5000, debug=True)

