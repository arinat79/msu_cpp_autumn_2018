#include <iostream>
#include <vector>
#include <sstream>

int search(std::string str, int &i) {
    int digit = 0;
    for (i; i < str.length(); ++i)
        switch (str[i]) {
            case '0'...'9':
                digit = digit * 10 + str[i] - '0';
                continue;
            case '}':
                return digit;
            default:
                throw std::runtime_error("incorrect input");
        }
    throw std::runtime_error("incorrect input");
}

template<class T>
void get_vector_elem(std::vector<std::string> &argv, T &&val) {
    std::stringstream buf;
    buf << val;
    argv.push_back(buf.str());
}

template<class T, class... Args>
void get_vector_elem(std::vector<std::string> &argv, T &&val, Args &&... args) {
    std::stringstream buf;
    buf << val;
    argv.push_back(buf.str());
    get_vector_elem(argv, std::forward<Args>(args)...);
}

std::string format(std::string &&str) {
    return str;
}

template<class... Args>
std::string format(std::string &&str, Args &&... args) {
    std::vector<std::string> argv;

    get_vector_elem(argv, std::forward<Args>(args)...);

    size_t new_str_len = str.length();
    for (int i = 0; i < argv.size(); ++i) {
        new_str_len += argv[i].length();
    }

    std::string formatted_string;

    int new_i = 0;
    for (int i = 0; i < str.length(); ++i, ++new_i) {
        if (str[i] == '{') {
            int number = search(str, ++i);
            if (number + 1 > argv.size())
                throw std::runtime_error("incorrect number of arguments");

            formatted_string.append(argv[number]);
        } else if (str[i] == '}')
            throw std::runtime_error("incorrect input");
        else
            formatted_string.push_back(str[i]);
    }
    return formatted_string;
}
