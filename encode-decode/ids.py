import random

def idsSim(string):
    randomInt = random.randint(0, 2)
    randomPos = random.randint(0, len(string))
    if randomInt == 0:
        string = insert(string, randomPos)
    elif randomInt == 1:
        string = delete(string, randomPos)
    else:
        string = substition(string, randomPos)
    return string


def insert(string, position):
    return string[:position] + randomBase() + string[position + 1:]

def delete(string, position):
    return string[:position] + string[position + 1:]

def substition(string, position):
    return string[:position - 1] + randomBase() + string[position + 1:]

def randomBase():
    return random.choice(["A", "T", "C", "G"])


def main():
    string = "ATGCATGC"
    print(idsSim(string))

main()