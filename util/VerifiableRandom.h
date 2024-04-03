// VerifiableRandom.h THIS IS THE WEB VERSION
/*

#pragma once
#include <emscripten.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class VerifiableRandom {
public:
    VerifiableRandom() = default;

    // Generates a random number in the range [min, max] using JavaScript's CSPRNG and returns its hash
    std::string generateRandomNumber(int min, int max, std::string& outHash) {
        if (min > max) {
            throw std::invalid_argument("min should not be greater than max");
        }

        int range = max - min + 1;
        int randomNumber = min + getCSPRNGNumber() % range;
        outHash = hash(std::to_string(randomNumber));

        return std::to_string(randomNumber);
    }

    // Verifies if the given number and hash match
    bool verifyRandomNumber(const std::string& number, const std::string& hash) {
        return this->hash(number) == hash;
    }

private:
    // Calls JavaScript to get a cryptographically secure random number
    int getCSPRNGNumber() {
        return emscripten_run_script_int("crypto.getRandomValues(new Uint32Array(1))[0]");
    }

    // Calls JavaScript to hash the input using SHA-256 and returns the hex string
    std::string hash(const std::string& input) {
        const int bufferSize = 64; // SHA-256 hex string length
        char buffer[bufferSize];
        emscripten_run_script_string(
                ("return Array.from(new Uint8Array(crypto.subtle.digestSync('SHA-256', new TextEncoder().encode('" + input + "')))).map(b => b.toString(16).padStart(2, '0')).join('')").c_str(),
                buffer,
                bufferSize
        );
        return std::string(buffer);
    }
};
*/


// VerifiableRandom.h

#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <stdexcept>
#include "datatypes.h"

class VerifiableRandom {
public:
    VerifiableRandom() = default;

    // Generates a random number in the range [min, max] using CSPRNG and returns its hash
    static std::string generateRandomNumber(int min, int max, std::string& outHash) {
        ASSERT(min <= max, "min should not be greater than max")

        int range = max - min + 1;
        int randomNumber = std::abs(getCSPRNGNumber()) % range + min;
        outHash = hash(std::to_string(randomNumber));

        return std::to_string(randomNumber);
    }

    // Verifies if the given number and hash match
    static bool verifyRandomNumber(const std::string& number, const std::string& hash) {
        return VerifiableRandom::hash(number) == hash;
    }

private:
    // Reads a random number from /dev/urandom
    static int getCSPRNGNumber() {
        std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
        ASSERT(urandom, "Failed to open /dev/urandom")

        int num;
        urandom.read(reinterpret_cast<char*>(&num), sizeof(num));
        ASSERT(urandom, "Failed to read from /dev/urandom")

        urandom.close();
        return num;
    }

    // Hashes the input using SHA-256 and returns the hex string
    static std::string hash(const std::string& input) {
        unsigned char hash[SHA512_DIGEST_LENGTH];
        SHA512_CTX sha512;
        SHA512_Init(&sha512);
        SHA512_Update(&sha512, input.c_str(), input.size());
        SHA512_Final(hash, &sha512);

        std::stringstream ss;
        for (unsigned char i : hash) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)i;
        }
        return ss.str();
    }
};
