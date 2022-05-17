def encode(message):
    binary = ''.join('{0:08b}'.format(ord(char), 'b') for char in message)
    return binary + '1' if binary.count('1') % 2 == 1 else binary + '0'
    

def decode(encoded_message):
    message = encoded_message[:-1]
    decoded_string = "".join(chr(int(binary, 2)) for binary in [message[i:i+8] for i in range(0, len(message), 8)])
    return decoded_string if message.count('1') % 2 == int(encoded_message[-1]) else "parity error"


def main():
    encoded = encode('hello')
    print(decode(encoded))

    encoded2 = encode("hello")
    encoded2 = encoded2[:-1] + '0'
    print(decode(encoded2))

main()