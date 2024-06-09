from flask import Flask, request, jsonify
from datetime import datetime

app = Flask(__name__)

sensor_data_list = [
    {
        "distance" : 15,
        "timestamp": "2022-11-25 22:10:00"
    },
    {
        "distance" : 5,
        "timestamp": "2022-11-25 22:10:05"
    }
]

@app.route('/sensor/data', methods=['POST', 'GET'])
def sensor_data():
    if request.method == 'POST':
        data = request.get_json()
        data['timestamp'] = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        sensor_data_list.append(data)
        print(data)
        return jsonify({'message': 'Data received!'})
    else:
        return jsonify(sensor_data_list)
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)