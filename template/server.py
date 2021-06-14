from flask import Flask, request
app = Flask(__name__)

@app.route('/')
def hello_world():
    print(request.environ)
    # print(dir(request))
    return 'Hello, World!'

app.run()
