#include "..\include\pipeline.hpp"

#include <cstddef>
#include <iostream>
#include <string>

#include "../lib/schifra/schifra_error_processes.hpp"
#include "../lib/schifra/schifra_galois_field.hpp"
#include "../lib/schifra/schifra_galois_field_polynomial.hpp"
#include "../lib/schifra/schifra_reed_solomon_block.hpp"
#include "../lib/schifra/schifra_reed_solomon_decoder.hpp"
#include "../lib/schifra/schifra_reed_solomon_encoder.hpp"
#include "../lib/schifra/schifra_sequential_root_generator_polynomial_creator.hpp"

// int main() {
//     /* Finite Field Parameters */
//     const std::size_t field_descriptor = 8;
//     const std::size_t generator_polynomial_index = 0;
//     const std::size_t generator_polynomial_root_count = 50;

//     /* Reed Solomon Code Parameters */
//     const std::size_t code_length = 255;
//     const std::size_t fec_length = 50;
//     const std::size_t data_length = code_length - fec_length;

//     /* Instantiate Finite Field and Generator Polynomials */
//     const schifra::galois::field field(field_descriptor,
//                                        schifra::galois::primitive_polynomial_size06,
//                                        schifra::galois::primitive_polynomial06);

//     schifra::galois::field_polynomial generator_polynomial(field);

//     if (
//         !schifra::make_sequential_root_generator_polynomial(field,
//                                                             generator_polynomial_index,
//                                                             generator_polynomial_root_count,
//                                                             generator_polynomial)) {
//         std::cout << "Error - Failed to create sequential root generator!" << std::endl;
//         return 1;
//     }

//     /* Instantiate Encoder and Decoder (Codec) */
//     typedef schifra::reed_solomon::encoder<code_length, fec_length, data_length> encoder_t;
//     typedef schifra::reed_solomon::decoder<code_length, fec_length, data_length> decoder_t;

//     const encoder_t encoder(field, generator_polynomial);
//     const decoder_t decoder(field, generator_polynomial_index);

//     std::string line = readFile("../files/chunked2.txt");

//     std::ofstream file2;
//     file2.open("../files/encoded2.txt");
//     std::vector<uint8_t> lineVec;

//     for (int i = 0; i < lineVec.size(); i += 205) {
//         std::string message = line.substr(i, 205);
//         /* Pad message with nulls up until the code-word length */
//         message.resize(code_length, 0x00);

//         // std::cout << "Original Message:  [" << message << "]" << std::endl;

//         /* Instantiate RS Block For Codec */
//         schifra::reed_solomon::block<code_length, fec_length> block;

//         /* Transform message into Reed-Solomon encoded codeword */
//         if (!encoder.encode(message, block)) {
//             std::cout << "Error - Critical encoding failure! "
//                       << "Msg: " << block.error_as_string() << std::endl;
//             return 1;
//         }

//         for (schifra::galois::field_symbol x : block.data) {
//             lineVec.push_back(x);
//             file2 << char(x);
//         }
//         file2 << '\n';
//     }
//     file2.close();

/* Add errors at every 3rd location starting at position zero */
// schifra::corrupt_message_all_errors00(block, 0, 3);

// std::cout << "Corrupted Codeword: [" << block << "]" << std::endl;

//    if (!decoder.decode(block))
//    {
//       std::cout << "Error - Critical decoding failure! "
//                 << "Msg: " << block.error_as_string()  << std::endl;
//       return 1;
//    }
//    else if (!schifra::is_block_equivelent(block, message))
//    {
//       std::cout << "Error - Error correction failed!" << std::endl;
//       return 1;
//    }

//    block.data_to_string(message);

//    std::cout << "Corrected Message: [" << message << "]" << std::endl;

//    std::cout << "Encoder Parameters [" << encoder_t::trait::code_length << ","
//                                        << encoder_t::trait::data_length << ","
//                                        << encoder_t::trait::fec_length  << "]" << std::endl;

//    std::cout << "Decoder Parameters [" << decoder_t::trait::code_length << ","
//                                        << decoder_t::trait::data_length << ","
//                                        << decoder_t::trait::fec_length  << "]" << std::endl;

//    return 0;
// }

std::vector<uint8_t> outerEncoder() {
    /* Finite Field Parameters */
    const std::size_t field_descriptor = 8;
    const std::size_t generator_polynomial_index = 0;
    const std::size_t generator_polynomial_root_count = 50;

    /* Reed Solomon Code Parameters */
    const std::size_t code_length = 255;
    const std::size_t fec_length = 50;
    const std::size_t data_length = code_length - fec_length;

    /* Instantiate Finite Field and Generator Polynomials */
    const schifra::galois::field field(field_descriptor,
                                       schifra::galois::primitive_polynomial_size06,
                                       schifra::galois::primitive_polynomial06);

    schifra::galois::field_polynomial generator_polynomial(field);

    if (
        !schifra::make_sequential_root_generator_polynomial(field,
                                                            generator_polynomial_index,
                                                            generator_polynomial_root_count,
                                                            generator_polynomial)) {
        std::cout << "Error - Failed to create sequential root generator!" << std::endl;
    }

    /* Instantiate Encoder and Decoder (Codec) */
    typedef schifra::reed_solomon::encoder<code_length, fec_length, data_length> encoder_t;
    typedef schifra::reed_solomon::decoder<code_length, fec_length, data_length> decoder_t;

    const encoder_t encoder(field, generator_polynomial);
    const decoder_t decoder(field, generator_polynomial_index);

    std::string line = readFile("../files/chunked2.txt");

    std::ofstream file2;
    file2.open("../files/encoded2.txt");
    std::vector<uint8_t> lineVec;
    for (int i = 0; i < line.size() - 1; i += 205) {
        std::string message = line.substr(i, 205);
        /* Pad message with nulls up until the code-word length */
        message.resize(code_length, 0x00);

        // std::cout << "Original Message:  [" << message << "]" << std::endl;

        /* Instantiate RS Block For Codec */
        schifra::reed_solomon::block<code_length, fec_length> block;

        /* Transform message into Reed-Solomon encoded codeword */
        if (!encoder.encode(message, block)) {
            std::cout << "Error - Critical encoding failure! "
                      << "Msg: " << block.error_as_string() << std::endl;
        }
        int count = 0;
        for (schifra::galois::field_symbol x : block.data) {
            lineVec.push_back(unsigned(x));
            count++;
            file2 << char(x);
        }
        file2 << '\n';
    }
    file2.close();
    return lineVec;
}