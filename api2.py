from flask import Flask, jsonify, request
from flask_cors import CORS
import json

# Initialize the Flask application
app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

# Define a route to create an endpoint
@app.route('/', methods=['GET'])
def home():
    return jsonify({"message": "Welcome to the Flask API!"})

# Example of a GET request with parameters

@app.route('/api/data', methods=['GET'])
def get_saved_data():
    try:
        # Open and read the saved data from the file
        with open('data.json', 'r') as f:
            saved_data = json.load(f)
        return jsonify(saved_data), 200  # Return the saved data as JSON
    except FileNotFoundError:
        return jsonify({"error": "No data found. Please save data first."}), 404

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

# Example of a PATCH request to update the data
@app.route('/api/data', methods=['PATCH'])
def patch_data():
    try:
        # Load the existing data
        with open('data.json', 'r') as f:
            saved_data = json.load(f)
        
        # Get the updated data from the request
        updated_data = request.get_json()

        # Update only the fields that are provided in the request
        saved_data.update(updated_data)

        # Save the updated data back to the file
        with open('data.json', 'w') as f:
            json.dump(saved_data, f, indent=4)

        response = {
            "message": "Data updated successfully",
            "updated_data": saved_data
        }
        return jsonify(response), 200

    except FileNotFoundError:
        return jsonify({"error": "No data found. Please save data first."}), 404

# Run the Flask app
if __name__ == '__main__':
    #app.run(debug=True)
    #app.run(host='192.168.43.105', port=5000, debug=True)
    app.run(host='192.168.0.15', port=5000, debug=True)


#This is the format of json
#curl -X POST http://192.168.0.15:5000/api/data -H "Content-Type: application/json" -d '{"Pin0": "OFF", "Pin1": "OFF", "Pin2": "OFF","Pin3": "OFF","Pin4": "OFF", "Pin5": "OFF", "Pin6": "OFF","Pin7": "OFF", "Pin8": "OFF"}'
