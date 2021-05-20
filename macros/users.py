import os

users = {}

print("Checking users running jobs")
os.system("condor_q -all -format \"%s \n\" Owner -idle > users.txt")
os.system("condor_q -all -format \"%s \n\" Owner -run >> users.txt")
os.system("condor_q -all -format \"%s \n\" Owner -held >> users.txt")
with open('users.txt') as watch:
    for line in watch:
        user = line.replace(" \n",'')
        if users.has_key(user):
            users[user] = users[user]+1
        else:
            users[user] = 1
print("Total Number Of Jobs By User: "+str(users))
users = {}
os.system("condor_q -all -format \"%s \n\" Owner -idle > users.txt")
with open('users.txt') as watch:
    for line in watch:
        user = line.replace(" \n",'')
        if users.has_key(user):
            users[user] = users[user]+1
        else:
            users[user] = 1
print("Total Number Of Idle Jobs By User: "+str(users))
users = {}
os.system("condor_q -all -format \"%s \n\" Owner -run > users.txt")
with open('users.txt') as watch:
    for line in watch:
        user = line.replace(" \n",'')
        if users.has_key(user):
            users[user] = users[user]+1
        else:
            users[user] = 1
print("Total Number Of Running Jobs By User: "+str(users))
users = {}
os.system("condor_q -all -format \"%s \n\" Owner -held > users.txt")
with open('users.txt') as watch:
    for line in watch:
        user = line.replace(" \n",'')
        if users.has_key(user):
            users[user] = users[user]+1
        else:
            users[user] = 1
print("Total Number Of Held Jobs By User: "+str(users))
