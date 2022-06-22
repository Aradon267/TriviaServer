import socket
import json
SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)
    msg = ""
    opt = input("1 For login\n2 For signup\n Enter: ")
    if opt == '1':
        username = input("Enter username: ")
        password = input("Enter password: ")
        login_msg = {
            "username": username,
            "password": password
        }
        json_msg = json.dumps(login_msg)
        msg += "1"
    elif opt == '2':
        username = input("Enter username: ")
        password = input("Enter password: ")
        mail = input("Enter mail: ")
        phone = input("Enter phone: ")
        addr = input("Enter addr: ")
        signup_msg = {
            "username": username,
            "password": password,
            "email": mail,
            "phone": phone,
            "addr": addr,
        }
        json_msg = json.dumps(signup_msg)
        msg += "2"

    msg += chr((len(json_msg) >> 24) & 0xFF)
    msg += chr((len(json_msg) >> 16) & 0xFF)
    msg += chr((len(json_msg) >> 8) & 0xFF)
    msg += chr(len(json_msg) & 0xFF)
    
    msg += json_msg
    print(msg)
    sock.send(msg.encode())
    resp = sock.recv(1024).decode()

    print("Client connected!\nThe server says: " + resp)
    sock.close()

if __name__ == "__main__":
    main();
