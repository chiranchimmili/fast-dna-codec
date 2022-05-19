import random

def idsSim(string):
    randomInt = random.randint(0, 2)
    randomPos = random.randint(0, len(string) - 1)
    randomBas = randomBase()
    if randomInt == 0:
        string = insert(string, randomPos, randomBas)
    elif randomInt == 1:
        string = delete(string, randomPos)
    else:
        while (randomBas == string[randomPos]):
            randomBas = randomBase()
        string = substition(string, randomPos, randomBas)
    return string

def insert(string, position, base):
    return string[:position] + base + string[position + 1:]

def delete(string, position):
    return string[:position] + string[position + 1:]

def substition(string, position, base):
    return string[:position] + base + string[position + 1:]

def randomBase():
    return random.choice(["A", "T", "C", "G"])

def idsOccurence(string, percentage):
    if random.random() < percentage:
        string = idsSim(string)
    return string

print(idsOccurence("ATCGATCG", 0.2))
