from flask import Flask, jsonify, request, json
from flask_cors import CORS, cross_origin
import firebase_admin
from firebase_admin import credentials, firestore
import os
import sys
from time import time


cred = credentials.Certificate(os.path.join(sys.path[0], 'qtproject-dbccc-firebase-adminsdk-tbo51-da1e0640e4.json'))
firebase_admin.initialize_app(cred)
db = firestore.client()

app = Flask(__name__)


@app.route('/api/add_to_do', methods=['POST'])
@cross_origin()
def add_to_do():
    request_data = json.loads(request.data)
    snap = db.collection("ToDo").add({
        "email": request_data["email"],
        "todo": request_data["todo"],
        "createdAt": time()
    })

    return {"id": snap[1].id, "todo": request_data["todo"]}, 200


@app.route('/api/delete_todo', methods=['POST'])
@cross_origin()
def delete_to_do():
    request_data = json.loads(request.data)
    id = request_data["id"]
    db.document(f"ToDo/{id}").delete()

    return {"Message": "Success"}, 200


@app.route('/api/update_todo', methods=['POST'])
@cross_origin()
def update_to_do():
    request_data = json.loads(request.data)
    id = request_data["id"]
    db.document(f"ToDo/{id}").update({
        "todo": request_data["todo"]
    })

    return {"Message": "Success"}, 200


@app.route('/api/get_todos/<email>', methods=['GET'])
@cross_origin()
def get_to_dos(email):
    res = db.collection("ToDo").where("email", "==", email).order_by("createdAt", "ASCENDING").get()

    res_dict = [item.to_dict() for item in res]
    for i, item in enumerate(res_dict):
        item["id"] = res[i].id

    return jsonify(res_dict), 200


if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0', port=int(os.environ.get('PORT', 8080)))