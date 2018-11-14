from flask import Flask
from flask import request

# Constants
DEBUG_LEVEL = True
FLASK_HOST = '0.0.0.0' # localhost

app = Flask(__name__)

@app.route('/dht22', methods = ['POST'])
def input():
  temperature = request.args.get('temperature')
  humidity = request.args.get('humidity')
  heat_index = request.args.get('heat_index')

  # TODO For now log request to file. Add database later.
  with open('log_dht22.txt', 'a') as f:
    f.write(temperature + ', ' + humidity + ', ' + heat_index + '\n')

  return temperature + ', ' + humidity + ', ' + heat_index

if __name__ == '__main__':
  app.run(debug = DEBUG_LEVEL, host = FLASK_HOST)
